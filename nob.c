/**
 * Copyright (c) 2025 mahd
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */
#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "./external/header/nob.h/nob.h"

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

bool build_raylib(Cmd *cmd) {
    //if (!mkdir_if_not_exists(BUILD_DIR "/raylib")) return 1;
    // Build raylib
    cmd_append(cmd, "make",
               temp_sprintf("RAYLIB_RELEASE_PATH=%s/raylib", BUILD_DIR),
               "PLATFORM=PLATFORM_DESKTOP",
               temp_sprintf("RAYLIB_MODULE_RAYGUI_PATH=%s/lib/raygui/src", EXTERNAL_DIR),
               "GLFW_LINUX_ENABLE_WAYLAND=TRUE",
               "RAYLIB_MODULE_RAYGUI=TRUE",
               "-C", temp_sprintf("%s/lib/raylib/src", EXTERNAL_DIR));
    return cmd_run_sync_and_reset(cmd);
}

bool build_Visonic(Cmd *cmd) {
    // Build Visonic
    cmd_append(cmd,
               "c++",
               "-o", temp_sprintf("%s/visonic", BUILD_DIR),
               "-Wall", "-Wextra",
               temp_sprintf("%s/main.cpp", SRC_DIR),
               "-static",
               temp_sprintf("-I%s/lib/raylib/src", EXTERNAL_DIR),
               temp_sprintf("-L%s/raylib", BUILD_DIR),
               "-lraylib", "-lm", "-ldl", "-lpthread", "-lGL", "-lrt");
    return cmd_run_sync_and_reset(cmd);
}

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Cmd cmd = {0};
    if (!init_env()) return 1;
    if (!build_raylib(&cmd)) return 1;
    //if (!build_Visonic(&cmd)) return 1;

  return 0;
}