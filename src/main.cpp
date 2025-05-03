// Copyright (c) 2025 mahd
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "../external/header/nob.h/nob.h"
#include "./header/nord.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "Visonic"

int main(int argc, char *argv[]) {
  NOB_UNUSED(argc);
  NOB_UNUSED(argv);
  nob_log(NOB_INFO,"Hello, World!\n");

  nob_log(NOB_INFO, "Arguments count: %d\n", argc);
  for (int i = 0; i < argc; i++) {
    nob_log(NOB_INFO, "Argument %d: %s\n", i, argv[i]);
  }
  return 0;
}