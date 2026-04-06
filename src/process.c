#include "process.h"

ProcessID create_child_process() {
  ProcessID child_process_id = fork();

  if (child_process_id == -1) {
    perror("fork");

    return -1;
  }

  return child_process_id;
}

BuiltInCommand built_in_commands[2] = {
  { .name = "cd", .execute = execute_change_directory },
  { .name = "exit", .execute = execute_exit }
};

int execute_change_directory(ArgumentsVector* arguments) {
  if (arguments->length <= 1) {
    fprintf(stderr, "cd: missing arguments\n");

    return 0;
  }

  int response = chdir(arguments->data[1]);
  if (response == -1) {
    perror("cd");
    return 0;
  }

  return 1;
}

int execute_exit(ArgumentsVector* arguments) {
  (void)arguments;

  exit(EXIT_SUCCESS);
}

int execute(ArgumentsVector* arguments) {
  if (arguments->length <= 0) {
    return -1;
  }

  int pipe_index = -1;

  for (int i = 0; i < arguments->length; i++) {
    char* argument = arguments->data[i];

    if (strcmp(argument, "|") == 0) {
      pipe_index = i;
    }
  }

  if (pipe_index != -1) {
    char** left_arguments = arguments->data;
    char** right_arguments = arguments->data + (pipe_index + 1);

    left_arguments[pipe_index] = NULL;

    int response = execute_pipe(left_arguments, right_arguments);

    if (response <= 0) {
      return response;
    }
  }

  int built_in_commands_size =
      sizeof(built_in_commands) / sizeof(built_in_commands[0]);

  for (int i = 0; i < built_in_commands_size; i++) {
    BuiltInCommand found_built_in_command = built_in_commands[i];

    if (strcmp(found_built_in_command.name, arguments->data[0]) == 0) {
      int response = found_built_in_command.execute(arguments);

      return response;
    }
  }

  ProcessID child_process_id = create_child_process();

  if (child_process_id == -1) {
    return -1;
  }

  ProcessStatus child_process_status;

  if (child_process_id == 0) {
    int child_process_response = execvp(arguments->data[0], arguments->data);

    if (child_process_response == -1) {
      perror(arguments->data[0]);
      exit(EXIT_FAILURE);
    }

    return child_process_response;
  }

  int wait_result;

  do {
    wait_result = waitpid(child_process_id, &child_process_status, 0);
  } while (wait_result == -1 && errno == EINTR);

  return 1;
}

int execute_pipe(char** left_arguments, char** right_arguments) {
  int file_descriptors[2];
  int response = pipe(file_descriptors);

  if (response == -1) {
    perror("pipe");
    return -1;
  }

  ProcessID left_process_id = fork();

  if (left_process_id == -1) {
    perror("fork");
    return -1;
  }

  ProcessStatus left_process_status;

  if (left_process_id == 0) {
    dup2(file_descriptors[1], STDOUT_FILENO);
    close(file_descriptors[0]);
    close(file_descriptors[1]);

    int response = execvp(left_arguments[0], left_arguments);

    if (response == -1) {
      perror(left_arguments[0]);
      _exit(EXIT_FAILURE);
      return -1;
    }

    _exit(EXIT_SUCCESS);
  } else {
    ProcessID right_process_id = fork();

    if (right_process_id == -1) {
      perror("fork");
      return -1;
    }

    ProcessStatus right_process_status;

    if (right_process_id == 0) {
      dup2(file_descriptors[0], STDIN_FILENO);
      close(file_descriptors[1]);
      close(file_descriptors[0]);

      int response = execvp(right_arguments[0], right_arguments);

      if (response == -1) {
        perror(right_arguments[0]);
        _exit(EXIT_FAILURE);
        return -1;
      }

      _exit(EXIT_SUCCESS);
    }

    close(file_descriptors[0]);
    close(file_descriptors[1]);
    waitpid(left_process_id, &left_process_status, 0);
    waitpid(right_process_id, &right_process_status, 0);
  }

  return 0;
}