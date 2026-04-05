#ifndef COMMON_H
#define COMMON_H

typedef char* String;
typedef char Buffer[BUFSIZ];

typedef struct {
  size_t capacity;
  size_t length;
  String data;
} Vector;

#endif