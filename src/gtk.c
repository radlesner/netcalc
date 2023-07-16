#include "headers/gtk.h"

#define GTK_WINDOW_WIDTH  400
#define GTK_WINDOW_LENGTH 300
#define BOX_MARGIN        10
#define BUTTON_MARGIN     5

static void on_window_closed()
{
    g_print("Window closed\n");
    gtk_main_quit();
}

void calculate_button_clicked() { g_print("Calculate button clicked!\n"); }

void gtkWindowInit(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    // Main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Netcalc");
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), GTK_WINDOW_WIDTH, GTK_WINDOW_LENGTH);

    // Making main box
    GtkWidget *box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL, BOX_MARGIN);
    gtk_container_add(GTK_CONTAINER(window), box_main);

    // Making box for textbox
    GtkWidget *box_fields = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box_main), box_fields, FALSE, FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(box_fields), BOX_MARGIN);

    // Making label "IP address"
    GtkWidget *label1 = gtk_label_new("IP address: ");
    gtk_box_pack_start(GTK_BOX(box_fields), label1, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(label1), 0.0);
    gtk_label_set_yalign(GTK_LABEL(label1), 0.5);

    // Making textbox "IP address"
    GtkWidget *entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Enter IP address");
    gtk_box_pack_start(GTK_BOX(box_fields), entry1, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entry1), 0.0);

    // Making label "Subnet mask"
    GtkWidget *label2 = gtk_label_new("    Subnet mask: ");
    gtk_box_pack_start(GTK_BOX(box_fields), label2, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(label2), 0.0);
    gtk_label_set_yalign(GTK_LABEL(label2), 0.5);
    // Making textbox "Subnet mask"
    GtkWidget *entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Enter subnet mask");
    gtk_box_pack_start(GTK_BOX(box_fields), entry2, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entry2), 0.0);

    // Making contener for a button
    GtkWidget *box_button = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(box_main), box_button, FALSE, FALSE, BUTTON_MARGIN);

    // Making button "Calculate"
    GtkWidget *calculate_button = gtk_button_new_with_label("Calculate");
    gtk_container_set_border_width(GTK_CONTAINER(calculate_button), BUTTON_MARGIN);
    g_signal_connect(calculate_button, "clicked", G_CALLBACK(calculate_button_clicked), NULL);
    gtk_box_pack_end(GTK_BOX(box_button), calculate_button, TRUE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return;
}
