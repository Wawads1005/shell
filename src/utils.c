#include "utils.h"

String get_current_working_directory(Buffer buffer) {
  String current_working_directory = getcwd(buffer, BUFSIZ);

  return current_working_directory;
}
