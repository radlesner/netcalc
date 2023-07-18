#include "headers/gtkMain.h"
#include "../headers/ipOperations.h"
#include "../headers/netInterfaces.h"
#include "../headers/segmentForOctet.h"
#include "../headers/validArguments.h"
#include "headers/gtkNetInterfaces.h"

#define GTK_WINDOW_WIDTH  880
#define GTK_WINDOW_LENGTH 300
#define BOX_MARGIN        10
#define BUTTON_MARGIN     5

GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *entry3;
GtkWidget *result_label_1;
GtkWidget *result_label_2;

static void on_combobox_changed(GtkComboBox *widget)
{
    GtkComboBoxText *combo_box     = GTK_COMBO_BOX_TEXT(widget);
    gchar *selected_text           = gtk_combo_box_text_get_active_text(combo_box);
    unsigned int ipAddrTab[4]      = {0, 0, 0, 0};
    unsigned int ipMaskTab[4]      = {0, 0, 0, 0};
    unsigned int ipWildTab[4]      = {0, 0, 0, 0};
    unsigned int ipNetAddrTab[4]   = {0, 0, 0, 0};
    unsigned int ipBroadAddrTab[4] = {0, 0, 0, 0};
    unsigned int ipFirstHost[4]    = {0, 0, 0, 0};
    unsigned int ipLastHost[4]     = {0, 0, 0, 0};
    unsigned int numHost;
    int maskPrefix;
    char result_text[1024];

    g_print("Selected interface: %s\n", selected_text);

    gtkGetInterfaceInfo(selected_text, ipAddrTab, ipMaskTab);
    maskPrefix = maskToPrefix(ipMaskTab);

    getWildAddr(ipWildTab, ipMaskTab);
    getNetworkAddr(ipNetAddrTab, ipAddrTab, ipMaskTab);
    getBroadAddr(ipBroadAddrTab, ipNetAddrTab, ipMaskTab);
    getFirstLastHost(ipFirstHost, ipLastHost, ipNetAddrTab, ipBroadAddrTab);
    numHost = getHostNumber(maskPrefix);

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
            "    Number of hosts		: %d\n"
            "\n"
            "\n"
            "\n",
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
            maskPrefix,
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

    gtk_label_set_text(GTK_LABEL(result_label_2), result_text);
    gtk_label_set_xalign(GTK_LABEL(result_label_2), 0.0);
    gtk_label_set_text(GTK_LABEL(result_label_2), result_text);

    g_free(selected_text);
}

static void on_window_closed()
{
    g_print("Window closed\n");
    gtk_main_quit();
}

static gboolean on_entry_activate()
{
    calculate_button_clicked();
    return TRUE;
}

void calculate_button_clicked()
{
    const char *ip_address         = gtk_entry_get_text(GTK_ENTRY(entry1));
    const char *subnet_mask_prefix = gtk_entry_get_text(GTK_ENTRY(entry2));

    unsigned int ipAddrTab[4]      = {0, 0, 0, 0};
    unsigned int ipMaskTab[4]      = {0, 0, 0, 0};
    unsigned int ipWildTab[4]      = {0, 0, 0, 0};
    unsigned int ipNetAddrTab[4]   = {0, 0, 0, 0};
    unsigned int ipBroadAddrTab[4] = {0, 0, 0, 0};
    unsigned int ipFirstHost[4]    = {0, 0, 0, 0};
    unsigned int ipLastHost[4]     = {0, 0, 0, 0};
    unsigned int numHost;

    char result_text[1024];

    if (isIPValid(ip_address) && isMaskValid(subnet_mask_prefix))
    {
        getOctet(ipAddrTab, ip_address);
        getMask(ipMaskTab, atoi(subnet_mask_prefix));
        getWildAddr(ipWildTab, ipMaskTab);
        getNetworkAddr(ipNetAddrTab, ipAddrTab, ipMaskTab);
        getBroadAddr(ipBroadAddrTab, ipNetAddrTab, ipMaskTab);
        getFirstLastHost(ipFirstHost, ipLastHost, ipNetAddrTab, ipBroadAddrTab);
        numHost = getHostNumber(atoi(subnet_mask_prefix));

        sprintf(result_text,
                "    IP address				: %d.%d.%d.%d\n"
                "\n"
                "    Mask address			: %d.%d.%d.%d\n"
                "    Wildcard address		: %d.%d.%d.%d\n"
                "\n"
                "    Network address		: %d.%d.%d.%d/%s\n"
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

        GtkLabel *result_label_widget = GTK_LABEL(result_label_1);
        PangoAttrList *attr_list      = pango_attr_list_new();
        PangoAttribute *attr          = pango_attr_foreground_new(65535, 65535, 65535); // White color
        attr->start_index             = 20;
        attr->end_index               = 49;
        pango_attr_list_insert(attr_list, attr);

        gtk_label_set_attributes(result_label_widget, attr_list);
        gtk_label_set_markup(result_label_widget, result_text);
    }
    else
    {
        sprintf(result_text,
                "    IP address				: BAD IP ADDRESS OR MASK PREFIX\n"
                "\n"
                "    Mask address			:\n"
                "    Wildcard address		:\n"
                "\n"
                "    Network address		:\n"
                "    Broadcast address		:\n"
                "    Firt address				:\n"
                "    Last address			:\n"
                "    Number of hosts		:\n");

        GtkLabel *result_label_widget = GTK_LABEL(result_label_1);
        PangoAttrList *attr_list      = pango_attr_list_new();
        PangoAttribute *attr          = pango_attr_foreground_new(65535, 0, 0); // Red color
        attr->start_index             = 20;
        attr->end_index               = 49;
        pango_attr_list_insert(attr_list, attr);

        gtk_label_set_attributes(result_label_widget, attr_list);
        gtk_label_set_markup(result_label_widget, result_text);
    }

    gtk_label_set_text(GTK_LABEL(result_label_1), result_text);
    gtk_label_set_xalign(GTK_LABEL(result_label_1), 0.0);
    gtk_label_set_text(GTK_LABEL(result_label_1), result_text);

    g_print("Calculate button clicked!\n");
}

// --------------------------------------------------------- GTK MAIN ---------------------------------------------------------

void gtkWindowInit(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    char blank_result_text_box1[182];
    sprintf(blank_result_text_box1,
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

    char blank_result_text_box2[256];
    sprintf(blank_result_text_box2,
            "    IP address				:\n"
            "\n"
            "    Mask address			:\n"
            "    Wildcard address		:\n"
            "\n"
            "    Network address		:\n"
            "    Broadcast address		:\n"
            "    Firt address				:\n"
            "    Last address			:\n"
            "    Number of hosts		:\n"
            "\n"
            "\n"
            "\n");

    // Main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Netcalc v3.2");
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), GTK_WINDOW_WIDTH, GTK_WINDOW_LENGTH);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // Making main box
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, BOX_MARGIN);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // ------------------ FIRST BOX ------------------

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, BOX_MARGIN);
    gtk_box_pack_start(GTK_BOX(main_box), box1, TRUE, TRUE, 0);

    // Making box for textbox
    GtkWidget *box_fields1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box1), box_fields1, FALSE, FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(box_fields1), BOX_MARGIN);

    // Making label "IP address"
    GtkWidget *label1 = gtk_label_new("IP address: ");
    gtk_box_pack_start(GTK_BOX(box_fields1), label1, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(label1), 0.0);
    gtk_label_set_yalign(GTK_LABEL(label1), 0.5);

    // Making textbox "IP address"
    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Enter IP address");
    gtk_box_pack_start(GTK_BOX(box_fields1), entry1, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entry1), 0.0);
    g_signal_connect(entry1, "activate", G_CALLBACK(on_entry_activate), NULL);

    // Making label "Subnet mask"
    GtkWidget *label2 = gtk_label_new("    Subnet prefix: ");
    gtk_box_pack_start(GTK_BOX(box_fields1), label2, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(label2), 0.0);
    gtk_label_set_yalign(GTK_LABEL(label2), 0.5);

    // Making textbox "Subnet mask"
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Enter mask prefix");
    gtk_box_pack_start(GTK_BOX(box_fields1), entry2, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entry2), 0.0);
    g_signal_connect(entry2, "activate", G_CALLBACK(on_entry_activate), NULL);

    // Making container for a button
    GtkWidget *box_button1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(box1), box_button1, FALSE, FALSE, BUTTON_MARGIN);

    // Making button "Calculate"
    GtkWidget *calculate_button1 = gtk_button_new_with_label("Calculate");
    gtk_container_set_border_width(GTK_CONTAINER(calculate_button1), BUTTON_MARGIN);
    g_signal_connect(calculate_button1, "clicked", G_CALLBACK(calculate_button_clicked), NULL);
    gtk_widget_set_hexpand(calculate_button1, FALSE);
    gtk_widget_set_vexpand(calculate_button1, FALSE);
    gtk_box_pack_start(GTK_BOX(box_button1), calculate_button1, FALSE, FALSE, 0);

    // Making result label
    result_label_1 = gtk_label_new(blank_result_text_box1);
    gtk_label_set_text(GTK_LABEL(result_label_1), blank_result_text_box1);
    gtk_label_set_xalign(GTK_LABEL(result_label_1), 0.0);
    gtk_box_pack_end(GTK_BOX(box1), result_label_1, TRUE, FALSE, 0);

    // ------------------ SECOND BOX ------------------

    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, BOX_MARGIN);
    gtk_box_pack_start(GTK_BOX(main_box), box2, TRUE, TRUE, 0);

    GtkWidget *fixed = gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(box2), fixed, TRUE, TRUE, 0);

    GtkComboBoxText *combo_box = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());

    // Ustaw marginesy kontenera fixed
    gtk_widget_set_margin_top(fixed, BOX_MARGIN);
    gtk_widget_set_margin_bottom(fixed, 0);
    gtk_widget_set_margin_start(fixed, 0);
    gtk_widget_set_margin_end(fixed, 250);

    gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(combo_box), 0, 0); // Dodanie combo box do kontenera fixed

    g_signal_connect(combo_box, "changed", G_CALLBACK(on_combobox_changed), NULL);

    // Shows connected interfaces to combo box
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(1);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr) continue;
        if (ifa->ifa_addr->sa_family == AF_INET) gtk_combo_box_text_append_text(combo_box, ifa->ifa_name);
    }
    if (ifaddr != NULL) freeifaddrs(ifaddr);

    // Making result label
    result_label_2 = gtk_label_new(blank_result_text_box2);
    gtk_label_set_text(GTK_LABEL(result_label_2), blank_result_text_box2);
    gtk_label_set_xalign(GTK_LABEL(result_label_2), 0.0);
    gtk_box_pack_end(GTK_BOX(box2), result_label_2, TRUE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();
}
