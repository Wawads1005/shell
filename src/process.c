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

int execute_change_directory(char** arguments) {
  if (arguments[1] == NULL) {
    fprintf(stderr, "cd: missing arguments\n");

    return 0;
  }

  int response = chdir(arguments[1]);
  if (response == -1) {
    perror("cd");
    return 0;
  }

  return 1;
}

int execute_exit(char** arguments) {
  (void)arguments;

  exit(EXIT_SUCCESS);
}

int execute(char** arguments) {
  if (arguments == NULL || arguments[0] == NULL) {
    return 1;
  }

  int built_in_commands_size =
      sizeof(built_in_commands) / sizeof(built_in_commands[0]);

  for (int i = 0; i < built_in_commands_size; i++) {
    BuiltInCommand found_built_in_command = built_in_commands[i];

    if (strcmp(found_built_in_command.name, arguments[0]) == 0) {
      int response = found_built_in_command.execute(arguments);

      return response;
    }
  }

  ProcessID child_process_id = create_child_process();

  if (child_process_id == -1) {
    return 0;
  }

  ProcessStatus child_process_status;

  if (child_process_id == 0) {
    int child_process_response = execvp(arguments[0], arguments);

    if (child_process_response == -1) {
      perror(arguments[0]);
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