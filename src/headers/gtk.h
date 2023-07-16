#include <glib.h>
#include <gtk/gtk.h>

static void on_window_closed();
void calculate_button_clicked(GtkWidget *widget, gpointer data);
void gtkWindowInit(int argc, char *argv[]);
void gtk_entry_get_ip_address(GtkEntry *entry, gpointer user_data);
void gtk_entry_get_subnet_mask(GtkEntry *entry, gpointer user_data);