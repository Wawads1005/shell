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

    if (ascii_character == EOF) {
      if (position == 0) {
        free(line);
        return NULL;
      }

      line[position] = '\0';
      return line;
    }

    if (ascii_character == NL) {
      line[position] = '\0';
      return line;
    }

    line[position] = (char)ascii_character;
    position++;

    if (position >= line_size - 1) {
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