#ifndef COMMON_H
#define COMMON_H

#define DEFINE_VECTOR(Type, Name) \
  typedef struct {                \
    Type* data;                   \
    size_t length;                \
    size_t capacity;              \
  } Name##Vector;

DEFINE_VECTOR(char, String)

#endif