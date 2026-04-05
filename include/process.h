#ifndef PROCESS_H
#define PROCESS_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#include "common.h"

typedef int ProcessID;
typedef int ProcessStatus;
typedef struct {
  char* name;
  int (*execute)(char**);
} BuiltInCommand;

ProcessID create_child_process();

int execute_change_directory(char** arguments);
int execute_exit(char** arguments);
int execute(char** argumemnts);

#endif