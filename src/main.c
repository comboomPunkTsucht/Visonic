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

static void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello World\n");
}
static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), WINDOW_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  gtk_window_set_child(GTK_WINDOW(window), box);

  button = gtk_button_new_with_label("Hello World");

  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);

  gtk_box_append(GTK_BOX(box), button);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  NOB_UNUSED(argc);
  NOB_UNUSED(argv);
  nob_log(NOB_INFO, "Hello World");
  GtkApplication *app;
  int status;

  app = gtk_application_new("app.comboompunktsucht."WINDOW_TITLE, G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
