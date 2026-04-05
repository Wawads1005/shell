#include "parser.h"

char** parse_arguments(char* line_data) {
  int arguments_capacity = BUFSIZ;
  int argument_length = 0;
  char** arguments = malloc(sizeof(char*) * arguments_capacity);

  if (arguments == NULL) {
    exit(EXIT_FAILURE);
  }

  char* argument = strtok(line_data, " ");

  while (argument != NULL) {
    if (argument_length >= arguments_capacity - 1) {
      arguments_capacity += BUFSIZ;

      char** resized_arguments =
          realloc(arguments, sizeof(char*) * arguments_capacity);

      if (resized_arguments == NULL) {
        free(arguments);
        exit(EXIT_FAILURE);
      }

      arguments = resized_arguments;
    }

    arguments[argument_length] = argument;
    argument_length++;

    argument = strtok(NULL, " ");
  }

  arguments[argument_length] = NULL;

  return arguments;
}
