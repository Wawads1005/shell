#include "parser.h"

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
