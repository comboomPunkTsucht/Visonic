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

void print_start(void)
{
  nob_log(NOB_INFO, "Hello World");
}
void print_exit(int status)
{
  nob_log(NOB_INFO, "good bye");
  nob_log(NOB_INFO, "Application exited with status: %d", status);
}

static void print_hello(GtkWidget *widget, gpointer data) {
  nob_log(NOB_INFO, "Hello World");
  nob_log(NOB_INFO, "Widget: %p", widget);
  nob_log(NOB_INFO, "Data: %p", data);
}

static void quit_cb(GtkWindow *window) {
  gtk_window_close(window);
}
static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), WINDOW_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new();

  /* Pack the container in the window */
  gtk_window_set_child(GTK_WINDOW(window), grid);

  button = gtk_button_new_with_label("Button 1");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label("Button 2");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label("Quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);

  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
  print_start();
  GtkApplication *app;
  int status;

  app = gtk_application_new("app.comboompunktsucht."WINDOW_TITLE, G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  print_exit(status);
  return status;
}
