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

    int response = execute(arguments);

    if (response == -1) {
      break;
    }

    free(current_working_directory);
    free(line);
    free(arguments);
  }

  return 0;
}
