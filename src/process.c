#include "process.h"

ProcessID create_child_process() {
  ProcessID child_process_id = fork();

  if (child_process_id < 0) {
    perror("fork");

    return -1;
  }

  return child_process_id;
}