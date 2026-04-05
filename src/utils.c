#include "utils.h"

char* get_current_working_directory() {
  char* current_working_directory = getcwd(NULL, 0);

  return current_working_directory;
}
