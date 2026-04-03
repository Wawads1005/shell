#include "utils.h"

String get_current_working_directory() {
  String current_working_directory = getcwd(NULL, 0);
}
