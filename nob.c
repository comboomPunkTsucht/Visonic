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
               "gcc",
               "-o", temp_sprintf("%s/visonic", BUILD_DIR),

               // CFLAGS
               "-Wall",
               "-Wextra",
               "-I", "/opt/homebrew/Cellar/gtk4/4.18.5/include/gtk-4.0",
               "-I", "/opt/homebrew/Cellar/pango/1.56.3/include/pango-1.0",
               "-I", "/opt/homebrew/Cellar/fribidi/1.0.16/include/fribidi",
               "-I", "/opt/homebrew/Cellar/harfbuzz/11.2.0/include/harfbuzz",
               "-I", "/opt/homebrew/Cellar/graphite2/1.3.14/include",
               "-I", "/opt/homebrew/include/gdk-pixbuf-2.0",
               "-I", "/opt/homebrew/opt/libtiff/include",
               "-I", "/opt/homebrew/opt/zstd/include",
               "-I", "/opt/homebrew/Cellar/xz/5.8.1/include",
               "-I", "/opt/homebrew/opt/jpeg-turbo/include",
               "-I", "/opt/homebrew/Cellar/cairo/1.18.4/include/cairo",
               "-I", "/opt/homebrew/Cellar/fontconfig/2.16.0/include",
               "-I", "/opt/homebrew/opt/freetype/include/freetype2",
               "-I", "/opt/homebrew/opt/libpng/include/libpng16",
               "-I", "/opt/homebrew/Cellar/libxext/1.3.6/include",
               "-I", "/opt/homebrew/Cellar/xorgproto/2024.1/include",
               "-I", "/opt/homebrew/Cellar/libxrender/0.9.12/include",
               "-I", "/opt/homebrew/Cellar/libx11/1.8.12/include",
               "-I", "/opt/homebrew/Cellar/libxcb/1.17.0/include",
               "-I", "/opt/homebrew/Cellar/libxau/1.0.12/include",
               "-I", "/opt/homebrew/Cellar/libxdmcp/1.1.5/include",
               "-I", "/opt/homebrew/Cellar/pixman/0.46.0/include/pixman-1",
               "-I", "/opt/homebrew/Cellar/graphene/1.10.8/include/graphene-1.0",
               "-I", "/opt/homebrew/Cellar/graphene/1.10.8/lib/graphene-1.0/include",
               "-I", "/opt/homebrew/Cellar/glib/2.84.1/include",
               "-I", "/Library/Developer/CommandLineTools/SDKs/MacOSX15.sdk/usr/include/ffi",
               "-I", "/opt/homebrew/Cellar/glib/2.84.1/include/glib-2.0",
               "-I", "/opt/homebrew/Cellar/glib/2.84.1/lib/glib-2.0/include",
               "-I", "/opt/homebrew/opt/gettext/include",
               "-I", "/opt/homebrew/Cellar/pcre2/10.45/include",

               // LDFLAGS
               "-L", "/opt/homebrew/Cellar/gtk4/4.18.5/lib",
               "-lgtk-4",
               "-L","/opt/homebrew/Cellar/pango/1.56.3/lib",
               "-lpangocairo-1.0",
               "-lpango-1.0",
               "-L","/opt/homebrew/Cellar/harfbuzz/11.2.0/lib",
               "-lharfbuzz",
               "-L","/opt/homebrew/lib",
               "-lgdk_pixbuf-2.0",
               "-L","/opt/homebrew/Cellar/cairo/1.18.4/lib",
               "-lcairo-gobject",
               "-lcairo",
               "-L","/opt/homebrew/Cellar/graphene/1.10.8/lib",
               "-lgraphene-1.0",
               "-L","/opt/homebrew/Cellar/glib/2.84.1/lib",
               "-lgio-2.0",
               "-lgobject-2.0",
               "-lglib-2.0",
               "-L","/opt/homebrew/opt/gettext/lib",
               "-lintl",

               temp_sprintf("%s/main.c", SRC_DIR));
    return cmd_run_sync_and_reset(cmd);
}

int main(int argc, char *argv[]) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Cmd cmd = {0};
    if (!init_env()) return 1;
    if (!build_Visonic(&cmd)) return 1;

  return 0;
}