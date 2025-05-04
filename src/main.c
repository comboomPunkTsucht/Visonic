// Copyright (c) 2025 mahd
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#define NOB_IMPLEMENTATION
#include "../external/header/nob.h/nob.h"
#include "./header/nord.h"
#include <gtk/gtk.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "Visonic"
#define TARGET_FPS 120

int main(int argc, char **argv)
{
  NOB_UNUSED(argc);
  NOB_UNUSED(argv);
  nob_log(NOB_INFO, "Hello World");

  return 0;
}
