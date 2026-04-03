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
  String name;
  int (*execute)(String*);
} BuiltInCommand;

ProcessID create_child_process();

int execute_change_directory(String* arguments);
int execute_exit(String* arguments);
int execute(String* argumemnts);

#endif