#include "parser.h"

String* parse_arguments(String line) {
  int arguments_capacity = BUFSIZ;
  String* arguments = malloc(sizeof(String) * arguments_capacity);

  if (arguments == NULL) {
    exit(EXIT_FAILURE);
  }

  int position = 0;

  String argument = strtok(line, " ");

  while (argument != NULL) {
    if (position >= arguments_capacity - 1) {
      arguments_capacity += BUFSIZ;

      String* resized_arguments =
          realloc(arguments, sizeof(String) * arguments_capacity);

      if (resized_arguments == NULL) {
        free(arguments);
        exit(EXIT_FAILURE);
      }

      arguments = resized_arguments;
    }

    arguments[position] = argument;
    position++;

    argument = strtok(NULL, " ");
  }

  arguments[position] = NULL;

  return arguments;
}
