// Copyright (c) 2025 mahd
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
extern "C" {
#  include "../external/header/nob.h/nob.h"
#  include "./header/nord.h"
} // extern "C"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "Visonic"

int main(int argc, char *argv[]) {
  NOB_UNUSED(argc);
  NOB_UNUSED(argv);
  printf("Hello, World!\n");

  printf("[INFO] Arguments count: %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("[INFO] Argument %d: %s\n", i, argv[i]);
  }
  return 0;
}