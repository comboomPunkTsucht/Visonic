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

void cmd_append_flags(Nob_Cmd *cmd, const char *flags) {
  char *copy = temp_strdup(flags);
  char *token = strtok(copy, " ");
  while (token != NULL) {
    cmd_append(cmd, token);
    token = strtok(NULL, " ");
  }
}
bool init_env() {
  BUILD_DIR = temp_sprintf("%s/build", get_current_dir_temp());
  SRC_DIR = temp_sprintf("%s/src", get_current_dir_temp());
  EXTERNAL_DIR = temp_sprintf("%s/external", get_current_dir_temp());
  return mkdir_if_not_exists(BUILD_DIR);
}

bool build_Visonic(Cmd *cmd) {
  Cmd cmd_cflags_gtk4 = {0};
  Cmd cmd_ldflags_gtk4 = {0};
  Fd fdout_cflags = fd_open_for_write(temp_sprintf("%s/cflags_gtk4_output.txt", BUILD_DIR));
  Fd fdout_ldflags = fd_open_for_write(temp_sprintf("%s/ldflags_gtk4_output.txt", BUILD_DIR));
  Fd fderr_cflags = fd_open_for_write(temp_sprintf("%s/cflags_gtk4_error.txt", BUILD_DIR));
  Fd fderr_ldflags = fd_open_for_write(temp_sprintf("%s/ldflags_gtk4_error.txt", BUILD_DIR));

  cmd_append(&cmd_cflags_gtk4,
             "pkg-config",
             "--cflags", "gtk4");
  cmd_append(&cmd_ldflags_gtk4,
             "pkg-config",
             "--libs", "gtk4");

  cmd_run_sync_redirect_and_reset(&cmd_cflags_gtk4, (Cmd_Redirect){
                                                        .fdin = NULL,
                                                        .fdout = &fdout_cflags,
                                                        .fderr = &fderr_cflags,
                                                    });
  cmd_run_sync_redirect_and_reset(&cmd_ldflags_gtk4, (Cmd_Redirect){
                                                         .fdin = NULL,
                                                         .fdout = &fdout_ldflags,
                                                         .fderr = &fderr_ldflags,
                                                     });

  String_Builder cflags_gtk4_sb = {0};
  read_entire_file(temp_sprintf("%s/cflags_gtk4_output.txt", BUILD_DIR), &cflags_gtk4_sb);
  String_View cflags_gtk4_trimmed = sv_trim(sb_to_sv(cflags_gtk4_sb));
  String_View cflags_gtk4 = nob_sv_chop_by_delim(&cflags_gtk4_trimmed, '\n');
  nob_log(INFO, "CFLAGS-GTK4: %s", cflags_gtk4.data);
  String_Builder ldflags_gtk4_sb = {0};
  read_entire_file(temp_sprintf("%s/ldflags_gtk4_output.txt", BUILD_DIR), &ldflags_gtk4_sb);
  String_View ldflags_gtk4_trimmed = sv_trim(sb_to_sv(ldflags_gtk4_sb));
  String_View ldflags_gtk4 = nob_sv_chop_by_delim(&ldflags_gtk4_trimmed, '\n');
  nob_log(INFO, "LDFLAGS-GTK4: %s", ldflags_gtk4.data);

  // Build Visonic
  cmd_append(cmd,
             "gcc",
             "-o", temp_sprintf("%s/visonic", BUILD_DIR),

             // CFLAGS
             "-Wall",
             "-Wextra");
  cmd_append_flags(cmd, cflags_gtk4.data);
  // LDFLAGS
  cmd_append_flags(cmd, ldflags_gtk4.data);
  cmd_append(cmd, temp_sprintf("%s/main.c", SRC_DIR));

  return cmd_run_sync_and_reset(cmd);
}

int main(int argc, char *argv[]) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    nob_log(INFO, "%d",isspace('\n'));
    Cmd cmd = {0};
    if (!init_env()) return 1;
    if (!build_Visonic(&cmd)) return 1;

  return 0;
}