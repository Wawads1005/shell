#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

#include "common.h"
#include "input.h"
#include "parser.h"
#include "process.h"
#include "utils.h"

int main(void) {
  while (true) {
    String current_working_directory = get_current_working_directory();

    printf("%s> ", current_working_directory);

    String line = readline();
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

    free(current_working_directory);
    free(line);
    free(arguments);
  }

  return 0;
}
