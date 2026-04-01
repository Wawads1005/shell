#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <unistd.h>

typedef int ProcessID;
typedef int ProcessStatus;

ProcessID create_child_process();

#endif