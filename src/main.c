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

    if (current_working_directory == NULL) {
      fprintf(stderr, "failed to get current working directory\n");
      break;
    }

    printf("%s> ", current_working_directory);
    free(current_working_directory);

    Vector* line = readline();

    if (line == NULL) {
      printf("\n");
      break;
    }

    String* arguments = parse_arguments(line->data);

    int response = execute(arguments);

    free(line);
    free(arguments);

    if (response == -1) {
      break;
    }
  }

  return 0;
}