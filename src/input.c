#include "input.h"

String readline() {
  int line_size = BUFSIZ;
  String line = malloc(sizeof(char) * line_size);

  if (line == NULL) {
    exit(EXIT_FAILURE);
  }

  int ascii_character;
  int position = 0;

  while (true) {
    ascii_character = getchar();

    switch (ascii_character) {
      case NL:
      case EOF:
        line[position] = '\0';

        return line;
      default:
        line[position] = (char)ascii_character;

        position++;
        break;
    }

    if (position >= (line_size - 1)) {
      line_size += BUFSIZ;
      String resized_line = realloc(line, sizeof(char) * line_size);

      if (resized_line == NULL) {
        free(line);
        exit(EXIT_FAILURE);
      }

      line = resized_line;
    }
  }
}