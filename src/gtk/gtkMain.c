#include "headers/gtkMain.h"
#include "../headers/ipOperations.h"
#include "../headers/netInterfaces.h"
#include "../headers/segmentForOctet.h"
#include "../headers/validArguments.h"
#include "headers/gtkNetInterfaces.h"

#define GTK_WINDOW_WIDTH  700
#define GTK_WINDOW_LENGTH 300
#define BOX_MARGIN        10
#define BUTTON_MARGIN     5

GtkWidget *entry1;
GtkWidget *entry2;

GtkWidget *labelIpAddressBox1;
GtkWidget *labelIpNetworkBox1;

GtkWidget *labelIpAddressBox2;
GtkWidget *labelIpNetworkBox2;

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
            "    IP address			: %d.%d.%d.%d\n"
            "    Mask address		: %d.%d.%d.%d\n"
            "    Wildcard address	: %d.%d.%d.%d",
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
            ipWildTab[3]);
    gtk_label_set_text(GTK_LABEL(labelIpAddressBox2), result_text);

    sprintf(result_text,
            "    Network address	: %d.%d.%d.%d/%d\n"
            "    Broadcast address	: %d.%d.%d.%d\n"
            "    First address		: %d.%d.%d.%d\n"
            "    Last address		: %d.%d.%d.%d\n"
            "    Number of hosts	: %d",
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
    gtk_label_set_text(GTK_LABEL(labelIpNetworkBox2), result_text);
}

static void on_window_closed()
{
    g_print("Window closed\n");
    gtk_main_quit();
}

void calculate_button_clicked()
{
    const char *ip_address = gtk_entry_get_text(GTK_ENTRY(entry1));
    const char *maskPrefix = gtk_entry_get_text(GTK_ENTRY(entry2));

    unsigned int ipAddrTab[4]      = {0, 0, 0, 0};
    unsigned int ipMaskTab[4]      = {0, 0, 0, 0};
    unsigned int ipWildTab[4]      = {0, 0, 0, 0};
    unsigned int ipNetAddrTab[4]   = {0, 0, 0, 0};
    unsigned int ipBroadAddrTab[4] = {0, 0, 0, 0};
    unsigned int ipFirstHost[4]    = {0, 0, 0, 0};
    unsigned int ipLastHost[4]     = {0, 0, 0, 0};
    unsigned int numHost;

    char result_text[1024];

    if (isIPValid(ip_address) && isMaskValid(maskPrefix))
    {
        getOctet(ipAddrTab, ip_address);
        getMask(ipMaskTab, atoi(maskPrefix));
        getWildAddr(ipWildTab, ipMaskTab);
        getNetworkAddr(ipNetAddrTab, ipAddrTab, ipMaskTab);
        getBroadAddr(ipBroadAddrTab, ipNetAddrTab, ipMaskTab);
        getFirstLastHost(ipFirstHost, ipLastHost, ipNetAddrTab, ipBroadAddrTab);
        numHost = getHostNumber(atoi(maskPrefix));

        sprintf(result_text,
                "    IP address			: %d.%d.%d.%d\n"
                "    Mask address		: %d.%d.%d.%d\n"
                "    Wildcard address	: %d.%d.%d.%d",
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
                ipWildTab[3]);
        gtk_label_set_text(GTK_LABEL(labelIpAddressBox1), result_text);

        sprintf(result_text,
                "    Network address	: %d.%d.%d.%d/%s\n"
                "    Broadcast address	: %d.%d.%d.%d\n"
                "    First address		: %d.%d.%d.%d\n"
                "    Last address		: %d.%d.%d.%d\n"
                "    Number of hosts	: %d",
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
        gtk_label_set_text(GTK_LABEL(labelIpNetworkBox1), result_text);
    }
    else
    {
        sprintf(result_text,
                "    IP address			: BAD IP ADDRESS OR MASK PREFIX\n"
                "    Mask address		:\n"
                "    Wildcard address	:");
        gtk_label_set_text(GTK_LABEL(labelIpAddressBox1), result_text);

        sprintf(result_text,
                "    Network address	:\n"
                "    Broadcast address	:\n"
                "    First address		:\n"
                "    Last address		:\n"
                "    Number of hosts	:");
        gtk_label_set_text(GTK_LABEL(labelIpNetworkBox1), result_text);
    }

    g_print("Calculate button clicked!\n");
}

// --------------------------------------------------------- GTK MAIN ---------------------------------------------------------

void gtkWindowInit(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    setlocale(LC_ALL, "");

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
    g_signal_connect(entry1, "activate", G_CALLBACK(calculate_button_clicked), NULL);

    // Making label "Subnet mask"
    GtkWidget *label2 = gtk_label_new("  /  ");
    gtk_box_pack_start(GTK_BOX(box_fields1), label2, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(label2), 0.0);
    gtk_label_set_yalign(GTK_LABEL(label2), 0.5);

    // Making textbox "Subnet mask"
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Enter mask prefix");
    gtk_box_pack_start(GTK_BOX(box_fields1), entry2, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entry2), 0.0);
    g_signal_connect(entry2, "activate", G_CALLBACK(calculate_button_clicked), NULL);

    // Frame "address address"
    GtkWidget *frameIpAddressBox1 = gtk_frame_new("Address settings");
    gtk_box_pack_start(GTK_BOX(box1), frameIpAddressBox1, TRUE, TRUE, 0);
    gtk_widget_set_margin_start(frameIpAddressBox1, 10);
    gtk_widget_set_margin_end(frameIpAddressBox1, 10);

    // Label for frame "ip address"
    labelIpAddressBox1 = gtk_label_new(
        "    IP address			:\n"
        "    Mask address		:\n"
        "    Wildcard address	:");
    gtk_label_set_xalign(GTK_LABEL(labelIpAddressBox1), 0.0);
    gtk_container_add(GTK_CONTAINER(frameIpAddressBox1), labelIpAddressBox1);

    // Frame "ip network"
    GtkWidget *frameIpNetworkBox1 = gtk_frame_new("Network properties");
    gtk_box_pack_start(GTK_BOX(box1), frameIpNetworkBox1, TRUE, TRUE, 0);
    gtk_widget_set_margin_start(frameIpNetworkBox1, 10);
    gtk_widget_set_margin_end(frameIpNetworkBox1, 10);
    gtk_widget_set_margin_bottom(frameIpNetworkBox1, 10);

    // Label for frame "ip network"
    labelIpNetworkBox1 = gtk_label_new(
        "    Network address	:\n"
        "    Broadcast address	:\n"
        "    First address		:\n"
        "    Last address		:\n"
        "    Number of hosts	:");
    gtk_label_set_xalign(GTK_LABEL(labelIpNetworkBox1), 0.0);
    gtk_container_add(GTK_CONTAINER(frameIpNetworkBox1), labelIpNetworkBox1);

    // ------------------ SECOND BOX ------------------

    // Create a vertical box to hold label and combo_box
    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, BOX_MARGIN);
    gtk_box_pack_start(GTK_BOX(main_box), box2, TRUE, TRUE, 0);

    // Create a horizontal box to hold the label and combo_box
    GtkWidget *box_label_and_combo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box2), box_label_and_combo, FALSE, FALSE, 0);

    // Create the label for the combo box
    GtkWidget *combo_label = gtk_label_new("Select an interface: ");
    gtk_box_pack_start(GTK_BOX(box_label_and_combo), combo_label, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(combo_label), 0.0);
    gtk_label_set_yalign(GTK_LABEL(combo_label), 0.7);

    // Create the combo box
    GtkWidget *fixed           = gtk_fixed_new();
    GtkComboBoxText *combo_box = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());
    gtk_box_pack_start(GTK_BOX(box_label_and_combo), fixed, TRUE, TRUE, 0);
    gtk_widget_set_margin_top(fixed, BOX_MARGIN);
    gtk_widget_set_margin_bottom(fixed, 0);
    gtk_widget_set_margin_start(fixed, 0);
    gtk_widget_set_margin_end(fixed, BOX_MARGIN);
    gtk_widget_set_size_request(GTK_WIDGET(combo_box), 175, -1);  // Width a combo_box
    gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(combo_box), 0, 0); // Add a combo_box to fixed contener
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

    // Frame "ip address"
    GtkWidget *frameIpAddressBox2 = gtk_frame_new("Interface settings");
    gtk_box_pack_start(GTK_BOX(box2), frameIpAddressBox2, TRUE, TRUE, 0);
    gtk_widget_set_margin_top(frameIpAddressBox2, 8);
    gtk_widget_set_margin_end(frameIpAddressBox2, 10);

    // Label for frame "ip address"
    labelIpAddressBox2 = gtk_label_new(
        "    IP address			:\n"
        "    Mask address		:\n"
        "    Wildcard address	:");
    gtk_label_set_xalign(GTK_LABEL(labelIpAddressBox2), 0.0);
    gtk_container_add(GTK_CONTAINER(frameIpAddressBox2), labelIpAddressBox2);

    // Frame "ip network"
    GtkWidget *frameIpNetworkBox2 = gtk_frame_new("Network properties");
    gtk_box_pack_start(GTK_BOX(box2), frameIpNetworkBox2, TRUE, TRUE, 0);
    gtk_widget_set_margin_end(frameIpNetworkBox2, 10);
    gtk_widget_set_margin_bottom(frameIpNetworkBox2, 10);

    // Label for frame "ip network"
    labelIpNetworkBox2 = gtk_label_new(
        "    Network address	:\n"
        "    Broadcast address	:\n"
        "    First address		:\n"
        "    Last address		:\n"
        "    Number of hosts	:");
    gtk_label_set_xalign(GTK_LABEL(labelIpNetworkBox2), 0.0);
    gtk_container_add(GTK_CONTAINER(frameIpNetworkBox2), labelIpNetworkBox2);

    gtk_widget_show_all(window);
    gtk_main();
}