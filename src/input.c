#include "input.h"

String readline(Buffer buffer) {
  String line = fgets(buffer, BUFSIZ, stdin);

  if (line == NULL) {
    return NULL;
  }

  line[strcspn(line, "\n")] = '\0';

  return line;
}