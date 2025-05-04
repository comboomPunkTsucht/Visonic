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

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  NOB_UNUSED(argc);
  NOB_UNUSED(argv);
  nob_log(NOB_INFO, "Hello World");
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
