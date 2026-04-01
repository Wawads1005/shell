#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

typedef char* String;
typedef char Buffer[BUFSIZ];
typedef int ProcessID;
typedef int ProcessStatus;

String readline(Buffer buffer);
String* parse_arguments(String line);
String get_current_working_directory(Buffer buffer);
ProcessID create_child_process();

int main(void) {
  while (true) {
    Buffer current_working_directory_buffer = "\0";
    String current_working_directory =
        get_current_working_directory(current_working_directory_buffer);

    printf("%s> ", current_working_directory);

    Buffer line_buffer = "\0";
    String line = readline(line_buffer);

    if (line == NULL) {
      break;
    }

    String* arguments = parse_arguments(line);

    if (strcmp(arguments[0], "exit") == 0) {
      break;
    }

    if (strcmp(arguments[0], "cd") == 0) {
      if (arguments[1] == NULL) {
        printf("cd: Missing argument\n");

        continue;
      }

      chdir(arguments[1]);

      continue;
    }

    ProcessID child_process_id = create_child_process();
    ProcessStatus child_status;

    if (child_process_id == 0) {
      execvp(arguments[0], arguments);
      perror(arguments[0]);

      exit(EXIT_FAILURE);
    }

    waitpid(child_process_id, &child_status, 0);

    free(arguments);
  }

  return 0;
}

String get_current_working_directory(Buffer buffer) {
  String current_working_directory = getcwd(buffer, BUFSIZ);

  return current_working_directory;
}

ProcessID create_child_process() {
  ProcessID child_process_id = fork();

  if (child_process_id < 0) {
    perror("fork");

    return -1;
  }

  return child_process_id;
}

String readline(Buffer buffer) {
  String line = fgets(buffer, BUFSIZ, stdin);

  if (line == NULL) {
    return NULL;
  }

  line[strcspn(line, "\n")] = '\0';

  return line;
}

String* parse_arguments(String line) {
  String* arguments = (String*)malloc(sizeof(String) * BUFSIZ);
  String argument = strtok(line, " ");

  int argument_count = 0;

  while (argument != NULL) {
    arguments[argument_count] = argument;
    argument_count++;

    argument = strtok(NULL, " ");
  }

  arguments[argument_count] = NULL;

  return arguments;
}
