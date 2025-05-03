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
static Flags GLOBAL_LDFLAGS = {0};
static Flags GLOBAL_CXXFLAGS = {0};
static Flags PLATFORM_CXXFLAGS = {0};
static Flags PLATFORM_LDFLAGS = {0};

bool init_env()
{
  BUILD_DIR = temp_sprintf("%s/build", get_current_dir_temp());
  SRC_DIR = temp_sprintf("%s/src", get_current_dir_temp());
  EXTERNAL_DIR = temp_sprintf("%s/external", get_current_dir_temp());
  da_append(&GLOBAL_LDFLAGS, temp_sprintf("-I%s/imgui", EXTERNAL_DIR));
  da_append(&GLOBAL_LDFLAGS, temp_sprintf("-I%s/imgui/backends", EXTERNAL_DIR));
  da_append(&GLOBAL_CXXFLAGS, "-Wall");
  da_append(&GLOBAL_CXXFLAGS, "-Wextra");
  da_append(&GLOBAL_CXXFLAGS, "-Wmissing-field-initializers");
#ifdef __APPLE__
  da_append(&PLATFORM_CXXFLAGS, "-framework");
  da_append(&PLATFORM_CXXFLAGS, "Cocoa");
  da_append(&PLATFORM_CXXFLAGS, "-framework");
  da_append(&PLATFORM_CXXFLAGS, "QuartzCore");
  da_append(&PLATFORM_LDFLAGS, "-L/usr/local/lib");
  da_append(&PLATFORM_LDFLAGS, "-I/usr/local/include");
  da_append(&PLATFORM_LDFLAGS, "-L/opt/homebrew/lib");
  da_append(&PLATFORM_LDFLAGS, "-I/opt/homebrew/include");
#endif
#ifdef __linux__
  da_append(&PLATFORM_CXXFLAGS, "-lX11");
  da_append(&PLATFORM_CXXFLAGS, "-lXext");
  da_append(&PLATFORM_CXXFLAGS, "-lXrender");
  da_append(&PLATFORM_CXXFLAGS, "-lXrandr");
  da_append(&PLATFORM_CXXFLAGS, "-lXi");
  da_append(&PLATFORM_LDFLAGS, "-L/usr/lib");
  da_append(&PLATFORM_LDFLAGS, "-I/usr/include");
#endif
#ifdef __FreeBSD__
  da_append(&PLATFORM_CXXFLAGS, "-lX11");
  da_append(&PLATFORM_CXXFLAGS, "-lXext");
  da_append(&PLATFORM_CXXFLAGS, "-lXrender");
  da_append(&PLATFORM_CXXFLAGS, "-lXrandr");
  da_append(&PLATFORM_CXXFLAGS, "-lXi");
  da_append(&PLATFORM_LDFLAGS, "-L/usr/lib");
  da_append(&PLATFORM_LDFLAGS, "-I/usr/include");
#endif
#ifdef __OpenBSD__
  da_append(&PLATFORM_CXXFLAGS, "-lX11");
  da_append(&PLATFORM_CXXFLAGS, "-lXext");
  da_append(&PLATFORM_CXXFLAGS, "-lXrender");
  da_append(&PLATFORM_CXXFLAGS, "-lXrandr");
  da_append(&PLATFORM_CXXFLAGS, "-lXi");
  da_append(&PLATFORM_LDFLAGS, "-L/usr/lib");
  da_append(&PLATFORM_LDFLAGS, "-I/usr/include");
#endif
#ifdef _WIN32
  da_append(&PLATFORM_CXXFLAGS, "-luser32");
  da_append(&PLATFORM_CXXFLAGS, "-lgdi32");
  da_append(&PLATFORM_CXXFLAGS, "-lcomdlg32");
  da_append(&PLATFORM_CXXFLAGS, "-lcomctl32");
  da_append(&PLATFORM_LDFLAGS, "-L/C/Program Files/lib");
  da_append(&PLATFORM_LDFLAGS, "-I/C/Program Files/include");
#endif
  return mkdir_if_not_exists(BUILD_DIR);
}

bool build_Visonic(Cmd *cmd) {
    // Build Visonic
    cmd_append(cmd,
               "g++",
               "-o", temp_sprintf("%s/visonic", BUILD_DIR));
    da_foreach(char *, global_ldflag, &GLOBAL_LDFLAGS) {
        cmd_append(cmd, global_ldflag);
    }
    da_foreach(char *, global_cxxflag, &GLOBAL_CXXFLAGS) {
      cmd_append(cmd, global_cxxflag);
    }
    da_foreach(char *, platform_cxxflag, &PLATFORM_CXXFLAGS) {
      cmd_append(cmd, platform_cxxflag);
    }
    da_foreach(char **, platform_ldflag, &PLATFORM_LDFLAGS) {
        cmd_append(cmd, platform_ldflag);
    }
    cmd_append(cmd, ctemp_sprintf("%s/main.cpp", SRC_DIR));
    return cmd_run_sync_and_reset(cmd);
}

int main(int argc, char *argv[]) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Cmd cmd = {0};
    if (!init_env()) return 1;
    if (!build_Visonic(&cmd)) return 1;

  return 0;
}