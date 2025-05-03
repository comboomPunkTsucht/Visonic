/**
 * Copyright (c) 2025 mahd
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */
#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "./external/header/nob.h/nob.h"

typedef struct {
  const char** items;
  size_t count;
  size_t capacity;
} Flags;

static char *BUILD_DIR = NULL;
static char *SRC_DIR = NULL;
static char *EXTERNAL_DIR = NULL;

bool init_env()
{
  BUILD_DIR = temp_sprintf("%s/build", get_current_dir_temp());
  SRC_DIR = temp_sprintf("%s/src", get_current_dir_temp());
  EXTERNAL_DIR = temp_sprintf("%s/external", get_current_dir_temp());
  return mkdir_if_not_exists(BUILD_DIR);
}

bool build_Visonic(Cmd *cmd) {
    // Build Visonic
    cmd_append(cmd,
               "g++",
               "-o", temp_sprintf("%s/visonic", BUILD_DIR),

               // LDFLAGS
               "-I", temp_sprintf("%s/lib/imgui", EXTERNAL_DIR),
               "-I", temp_sprintf("%s/lib/imgui/backends", EXTERNAL_DIR),

               // CXXFLAGS
               "-Wall",
               "-Wextra",
               "-Wmissing-field-initializers");
#ifdef __APPLE__
    cmd_append(cmd,
               // CXXFLAGS
               "-framework", "Metal",
               "-framework", "MetalKit",
               "-framework", "Cocoa",
               "-framework", "IOKit",
               "-framework", "CoreVideo",
               "-framework", "QuartzCore",

               // LDFLAGS
               "-L", "/usr/local/lib",
               "-I", "/usr/local/include",
               "-L", "/opt/homebrew/lib",
               "-I", "/opt/homebrew/include",
               "-lglfw");
#endif
#ifdef __linux__
    cmd_append(cmd,
      //CXXFLAGS
            "-lX11",
            "-lXext",
            "-lXrender",
            "-lXrandr",
            "-lXi",

          //LDFLAGS
            "-L/usr/lib",
            "-I/usr/include");
#endif
#ifdef __FreeBSD__
    cmd_append(cmd,
      //CXXFLAGS
            "-lX11",
            "-lXext",
            "-lXrender",
            "-lXrandr",
            "-lXi",

          //LDFLAGS
            "-L/usr/lib",
            "-I/usr/include");
#endif
#ifdef __OpenBSD__
    cmd_append(cmd,
      //CXXFLAGS
            "-lX11",
            "-lXext",
            "-lXrender",
            "-lXrandr",
            "-lXi",

          //LDFLAGS
            "-L/usr/lib",
            "-I/usr/include");
#endif
#ifdef _WIN32
    cmd_append(cmd,
      //CXXFLAGS
            "-luser32",
            "-lgdi32",
            "-lcomdlg32",
            "-lcomctl32",

          //LDFLAGS
            "-L/C/Program Files/lib",
            "-I/C/Program Files/include");
#endif

    cmd_append(cmd, temp_sprintf("%s/main.mm", SRC_DIR), temp_sprintf("%s/lib/imgui/imgui.cpp", EXTERNAL_DIR), temp_sprintf("%s/lib/imgui/imgui_draw.cpp", EXTERNAL_DIR), temp_sprintf("%s/lib/imgui/imgui_widgets.cpp", EXTERNAL_DIR), temp_sprintf("%s/lib/imgui/imgui_tables.cpp", EXTERNAL_DIR), temp_sprintf("%s/lib/imgui/imgui_demo.cpp", EXTERNAL_DIR), temp_sprintf("%s/lib/imgui/backends/imgui_impl_glfw.cpp", EXTERNAL_DIR), temp_sprintf("%s/lib/imgui/backends/imgui_impl_metal.mm", EXTERNAL_DIR));
    return cmd_run_sync_and_reset(cmd);
}

int main(int argc, char *argv[]) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Cmd cmd = {0};
    if (!init_env()) return 1;
    if (!build_Visonic(&cmd)) return 1;

  return 0;
}