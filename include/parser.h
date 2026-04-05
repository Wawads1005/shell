#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define INITIAL_ARGUMENTS_CAPACITY 8

DEFINE_VECTOR(char*, Arguments)

ArgumentsVector* parse_arguments(char* line);

#endif