#include "input.h"

Vector* readline() {
  Vector* line = malloc(sizeof(Vector));

  if (line == NULL) {
    exit(EXIT_FAILURE);
  }

  line->capacity = BUFSIZ;
  line->data = malloc(line->capacity);
  line->length = 0;

  if (line->data == NULL) {
    free(line);
    exit(EXIT_FAILURE);
  }

  int ascii_character;

  while (true) {
    ascii_character = getchar();

    if (ascii_character == EOF) {
      if (line->length == 0) {
        free(line->data);
        free(line);
        return NULL;
      }

      line->data[line->length] = '\0';
      return line;
    }

    if (ascii_character == NL) {
      line->data[line->length] = '\0';
      return line;
    }

    if (line->length >= line->capacity - 1) {
      line->capacity += BUFSIZ;

      String resized_line_data = realloc(line->data, line->capacity);

      if (resized_line_data == NULL) {
        free(line->data);
        free(line);
        exit(EXIT_FAILURE);
      }

      line->data = resized_line_data;
    }

    line->data[line->length] = (char)ascii_character;
    line->length++;
  }
}