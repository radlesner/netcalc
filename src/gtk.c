#include "headers/gtk.h"
#include "headers/ipOperations.h"
#include "headers/segmentForOctet.h"
#include "headers/validArguments.h"

#define GTK_WINDOW_WIDTH  400
#define GTK_WINDOW_LENGTH 300
#define BOX_MARGIN        10
#define BUTTON_MARGIN     5

GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *result_label;

static void on_window_closed()
{
    g_print("Window closed\n");
    gtk_main_quit();
}

void calculate_button_clicked(GtkWidget *widget, gpointer data)
{
    char *ip_address             = gtk_entry_get_text(GTK_ENTRY(entry1));
    char *subnet_mask_prefix_str = gtk_entry_get_text(GTK_ENTRY(entry2));

    unsigned int ipAddrTab[4]      = {0, 0, 0, 0};
    unsigned int ipMaskTab[4]      = {0, 0, 0, 0};
    unsigned int ipWildTab[4]      = {0, 0, 0, 0};
    unsigned int ipNetAddrTab[4]   = {0, 0, 0, 0};
    unsigned int ipBroadAddrTab[4] = {0, 0, 0, 0};
    unsigned int ipFirstHost[4]    = {0, 0, 0, 0};
    unsigned int ipLastHost[4]     = {0, 0, 0, 0};
    unsigned int numHost;

    char result_text[1024]; // Przykładowa długość tablicy wynikowej

    if (!isIPValid(ip_address) && !isMaskValid(subnet_mask_prefix_str))
    {
        printf("IP is not valid\n");
        return;
    }
    else
    {
        printf("IP is valid\n");

        int subnet_mask_prefix = atoi(subnet_mask_prefix_str);

        getOctet(ipAddrTab, ip_address);
        getMask(ipMaskTab, subnet_mask_prefix);
        getWildAddr(ipWildTab, ipMaskTab);
        getNetworkAddr(ipNetAddrTab, ipAddrTab, ipMaskTab);
        getBroadAddr(ipBroadAddrTab, ipNetAddrTab, ipMaskTab);
        getFirstLastHost(ipFirstHost, ipLastHost, ipNetAddrTab, ipBroadAddrTab);
        numHost = getHostNumber(subnet_mask_prefix);

        sprintf(result_text,
                "    IP address				: %d.%d.%d.%d\n"
                "\n"
                "    Mask address			: %d.%d.%d.%d\n"
                "    Wildcard address		: %d.%d.%d.%d\n"
                "\n"
                "    Network address		: %d.%d.%d.%d/%d\n"
                "    Broadcast address		: %d.%d.%d.%d\n"
                "    Firt address				: %d.%d.%d.%d\n"
                "    Last address			: %d.%d.%d.%d\n"
                "    Number of hosts		: %d\n",
                // IP address
                ipAddrTab[0],
                ipAddrTab[1],
                ipAddrTab[2],
                ipAddrTab[3],
                // Mask address
                ipMaskTab[0],
                ipMaskTab[1],
                ipMaskTab[2],
                ipMaskTab[3],
                // Wildcard address
                ipWildTab[0],
                ipWildTab[1],
                ipWildTab[2],
                ipWildTab[3],
                // Network address
                ipNetAddrTab[0],
                ipNetAddrTab[1],
                ipNetAddrTab[2],
                ipNetAddrTab[3],
                // Prefix
                subnet_mask_prefix,
                // Broadcast address
                ipBroadAddrTab[0],
                ipBroadAddrTab[1],
                ipBroadAddrTab[2],
                ipBroadAddrTab[3],
                // Firt address
                ipFirstHost[0],
                ipFirstHost[1],
                ipFirstHost[2],
                ipFirstHost[3],
                // Last address
                ipLastHost[0],
                ipLastHost[1],
                ipLastHost[2],
                ipLastHost[3],
                // Number of hosts
                numHost);

        gtk_label_set_text(GTK_LABEL(result_label), result_text);
        gtk_label_set_xalign(GTK_LABEL(result_label), 0.0);
        gtk_label_set_text(GTK_LABEL(result_label), result_text);
    }

    g_print("Calculate button clicked!\n");
}

void gtkWindowInit(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    char blank_result_text[1024];
    sprintf(blank_result_text,
            "    IP address				:\n"
            "\n"
            "    Mask address			:\n"
            "    Wildcard address		:\n"
            "\n"
            "    Network address		:\n"
            "    Broadcast address		:\n"
            "    Firt address				:\n"
            "    Last address			:\n"
            "    Number of hosts		:\n");

    // Main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Netcalc");
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), GTK_WINDOW_WIDTH, GTK_WINDOW_LENGTH);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

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
    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Enter IP address");
    gtk_box_pack_start(GTK_BOX(box_fields), entry1, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entry1), 0.0);

    // Making label "Subnet mask"
    GtkWidget *label2 = gtk_label_new("    Subnet prefix: ");
    gtk_box_pack_start(GTK_BOX(box_fields), label2, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(label2), 0.0);
    gtk_label_set_yalign(GTK_LABEL(label2), 0.5);

    // Making textbox "Subnet mask"
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Enter subnet mask");
    gtk_box_pack_start(GTK_BOX(box_fields), entry2, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entry2), 0.0);

    // Making container for a button
    GtkWidget *box_button = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(box_main), box_button, FALSE, FALSE, BUTTON_MARGIN);

    // Making button "Calculate"
    GtkWidget *calculate_button = gtk_button_new_with_label("Calculate");
    gtk_container_set_border_width(GTK_CONTAINER(calculate_button), BUTTON_MARGIN);
    g_signal_connect(calculate_button, "clicked", G_CALLBACK(calculate_button_clicked), NULL);
    gtk_box_pack_end(GTK_BOX(box_button), calculate_button, TRUE, FALSE, 0);

    // Making result label
    result_label = gtk_label_new(blank_result_text);
    gtk_label_set_text(GTK_LABEL(result_label), blank_result_text);
    gtk_label_set_xalign(GTK_LABEL(result_label), 0.0);
    gtk_box_pack_end(GTK_BOX(box_main), result_label, TRUE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();
}
