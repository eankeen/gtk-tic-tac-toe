// #include <stdlib.h>
// #include <stdlib.h>
#include <gtk/gtk.h>

static GtkWidget *number1;
static GtkWidget *number2;
static GtkWidget *result;

int count = 0;

static void do_calculate(GtkWidget *calculate, gpointer data) {
  int num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(number1)));
  int num2 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(number2)));

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "result: %d", num1 + num2);

  gtk_label_set_text(GTK_LABEL(result), buffer);
}

static void count_button(GtkWidget *widget, gpointer ptr) {
  char buffer[30];
  count++;
  sprintf(buffer, "Button pressed %d times", count);
  gtk_button_set_label(GTK_BUTTON(ptr), buffer);
}

static void print_hello(GtkWidget *widget, gpointer data) {
  g_print("Hello World\n");
}

static void activate (GtkApplication* app, gpointer data) {
  // window
  GtkWidget *window;
  window = gtk_application_window_new (app);
  gtk_window_set_title(GTK_WINDOW(window), "Tic Tac Toe");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // grid
  GtkWidget *grid;
  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  // btn
  GtkWidget *btn;
  btn = gtk_button_new_with_label("Some Text");
  g_signal_connect(btn, "clicked", G_CALLBACK(count_button), btn);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn), 0, 0, 1, 1);

  GtkWidget *btn2;
  btn2 = gtk_button_new_with_label("Other text");
  g_signal_connect(btn2, "clicked", G_CALLBACK(count_button), btn2); 
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn2), 1, 1, 1, 1);

  GtkWidget *btn3;
  btn3 = gtk_button_new_with_label("Some Text");
  g_signal_connect(btn3, "clicked", G_CALLBACK(count_button), btn3);
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(btn3), 2, 0, 1, 1);

  // entries
  number1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), number1, 0, 2, 1, 1);

  number2 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), number2, 1, 2, 1, 1);

  GtkWidget *calculate;
  calculate = gtk_button_new_with_label("calculate");
  g_signal_connect(calculate, "clicked", G_CALLBACK(do_calculate), NULL);
  gtk_grid_attach(GTK_GRID(grid), calculate, 3, 3, 1, 1);
  result = gtk_label_new("result: ");
  gtk_grid_attach(GTK_GRID(grid), result, 0, 3, 1, 1);

  // init
  gtk_widget_show_all(window);
  gtk_main();

  return;
}

int main(int argc, char *argv[]) {
  GtkApplication *app;
  short int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
