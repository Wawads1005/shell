#include "parser.h"

ArgumentsVector* parse_arguments(StringVector* line) {
  ArgumentsVector* arguments = malloc(sizeof(ArgumentsVector));

  if (arguments == NULL) {
    exit(EXIT_FAILURE);
  }

  arguments->capacity = INITIAL_ARGUMENTS_CAPACITY;
  arguments->length = 0;
  arguments->data = malloc(sizeof(char*) * arguments->capacity);

  if (arguments->data == NULL) {
    free(arguments);
    exit(EXIT_FAILURE);
  }

  char* argument = strtok(line->data, " ");

  while (argument != NULL) {
    if (arguments->length >= arguments->capacity - 1) {
      arguments->capacity += INITIAL_ARGUMENTS_CAPACITY;

      char** resized_arguments =
          realloc(arguments->data, sizeof(char*) * arguments->capacity);

      if (resized_arguments == NULL) {
        free(arguments->data);
        free(arguments);
        exit(EXIT_FAILURE);
      }

      arguments->data = resized_arguments;
    }

    arguments->data[arguments->length] = argument;
    arguments->length++;

    argument = strtok(NULL, " ");
  }

  arguments->data[arguments->length] = NULL;

  return arguments;
}
