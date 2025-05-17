#include "headers/gtkMain.h"
#include "headers/gtkOutputSignals.h"

#define WINDOW_RESIZABLE          FALSE
#define GTK_WINDOW_WIDTH          500
#define GTK_WINDOW_HEIGHT         100
#define BOX_MARGIN                10
#define FONT_STYLE                "Source Code Pro Light"
#define FONT_OUTPUT_SIZE          13
#define FONT_OUTPUT_VERSION_SIZE  10
#define COMBO_BOX_WIDTH           190
#define FRAME_LABEL_MARGIN_START  10
#define FRAME_LABEL_MARGIN_END    10
#define FRAME_LABEL_MARGIN_TOP    10
#define FRAME_LABEL_MARGIN_BOTTOM 10

GtkWidget *entryIpAddress;
GtkWidget *entryMaskPrefix;
GtkWidget *labelFrameBox1;
GtkWidget *labelFrameBox2;
GtkWidget *labelFrameInterfaceConfigOutput;
GtkWidget *labelFrameDnsConfig;

// -------------------------------------------------------------
static void comboBoxAddOptions(GtkComboBoxText *comboBoxInterface)
{
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(1);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr)
        {
            continue;
        }

        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            gtk_combo_box_text_append_text(comboBoxInterface, ifa->ifa_name);
        }
    }

    if (ifaddr != NULL)
        freeifaddrs(ifaddr);
}

// -------------------------------------------------------------
_Noreturn static void on_window_closed(void)
{
    g_print("Window closed\n");
    gtk_main_quit();
    exit(0);
}

// -------------------------------------------------------------
static void setLabelOutputFont(GtkWidget *label, char *fontName, int fontSize)
{
    PangoFontDescription *fontGtkOutput = pango_font_description_new();
    pango_font_description_set_family(fontGtkOutput, fontName);
    pango_font_description_set_absolute_size(fontGtkOutput, fontSize * PANGO_SCALE);

    gchar *cssFontGtkOutput = g_strdup_printf(
        "* { font-family: \"%s\"; font-size: %dpx; }", pango_font_description_get_family(fontGtkOutput), (int)pango_font_description_get_size(fontGtkOutput) / PANGO_SCALE);
    GtkCssProvider *providerFontGtkOutput = gtk_css_provider_new();
    gtk_css_provider_load_from_data(providerFontGtkOutput, cssFontGtkOutput, -1, NULL);
    g_free(cssFontGtkOutput);

    gtk_style_context_add_provider(gtk_widget_get_style_context(label), GTK_STYLE_PROVIDER(providerFontGtkOutput), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(providerFontGtkOutput);
    pango_font_description_free(fontGtkOutput);
}

// -------------------------------------------------------------
static void printVersion(GtkWidget *box)
{
    GtkWidget *boxVersionProgramBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box), boxVersionProgramBox, TRUE, TRUE, 0);
    gtk_widget_set_margin_start(boxVersionProgramBox, 2);

    char versionProgramOutput[24];
    sprintf(versionProgramOutput, "v%s", VERSION_PROGRAM);

    GtkWidget *labelVersionProgram = gtk_label_new(versionProgramOutput);
    gtk_container_add(GTK_CONTAINER(boxVersionProgramBox), labelVersionProgram);
    gtk_label_set_yalign(GTK_LABEL(labelVersionProgram), 1);

    setLabelOutputFont(labelVersionProgram, FONT_STYLE, FONT_OUTPUT_VERSION_SIZE);
}

// --------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------- GTK MAIN --------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------
void gtkWindowInit(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    setlocale(LC_ALL, "");

    char blankOutput[126];
    char blankOutputInterface[45];
    char blankOutputDnsConfig[65];

    sprintf(blankOutput,
            "IP address:\n"
            "Mask address:\n"
            "Wildcard address:\n"
            "Network address:\n"
            "Broadcast address:\n"
            "First address:\n"
            "Last address:\n"
            "Number of hosts:");

    sprintf(blankOutputInterface,
            "Configuration:\n"
            "MAC address:\n"
            "Gateway address:");

    sprintf(blankOutputDnsConfig,
            "DNS:\n"
            "DNS address 1:\n"
            "DNS address 2:\n"
            "DNS address 3:\n"
            "DNS address 4:");

    // Main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Netcalc");
    gtk_window_set_default_size(GTK_WINDOW(window), GTK_WINDOW_WIDTH, GTK_WINDOW_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(window), WINDOW_RESIZABLE);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);

    // Making main box
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // ------------------ FIRST BOX ------------------

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, BOX_MARGIN);
    gtk_box_pack_start(GTK_BOX(main_box), box1, TRUE, TRUE, 0);

    // Making box for textbox
    GtkWidget *fieldTextBox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box1), fieldTextBox1, FALSE, FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(fieldTextBox1), BOX_MARGIN);

    // Making label "IP address"
    GtkWidget *labelIpAddressBox1 = gtk_label_new("IP address: ");
    gtk_box_pack_start(GTK_BOX(fieldTextBox1), labelIpAddressBox1, FALSE, FALSE, 0);

    // Making textbox "IP address"
    entryIpAddress = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryIpAddress), "Enter IP address");
    gtk_box_pack_start(GTK_BOX(fieldTextBox1), entryIpAddress, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entryIpAddress), 0.0);
    g_signal_connect(entryIpAddress, "activate", G_CALLBACK(calcButtonClick), NULL);

    // Making label "Subnet mask prefix"
    GtkWidget *labelPrefixBox1 = gtk_label_new("  /  ");
    gtk_box_pack_start(GTK_BOX(fieldTextBox1), labelPrefixBox1, FALSE, FALSE, 0);

    // Making textbox "Subnet mask prefix"
    entryMaskPrefix = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(entryMaskPrefix), 2);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryMaskPrefix), "24");
    gtk_box_pack_start(GTK_BOX(fieldTextBox1), entryMaskPrefix, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entryMaskPrefix), 0.0);
    g_signal_connect(entryMaskPrefix, "activate", G_CALLBACK(calcButtonClick), NULL);

    // Frame "address address"
    GtkWidget *frameAddressOutput = gtk_frame_new("Network properties");
    gtk_box_pack_start(GTK_BOX(box1), frameAddressOutput, TRUE, TRUE, 0);

    gtk_widget_set_margin_start(frameAddressOutput, 10);
    gtk_widget_set_margin_end(frameAddressOutput, 10);
    gtk_widget_set_margin_top(frameAddressOutput, 0);
    gtk_widget_set_margin_bottom(frameAddressOutput, 0);

    // Label for frame "ip address"
    labelFrameBox1 = gtk_label_new(blankOutput);
    gtk_label_set_xalign(GTK_LABEL(labelFrameBox1), 0.0);
    gtk_container_add(GTK_CONTAINER(frameAddressOutput), labelFrameBox1);

    gtk_widget_set_margin_start(labelFrameBox1, FRAME_LABEL_MARGIN_START);
    gtk_widget_set_margin_end(labelFrameBox1, FRAME_LABEL_MARGIN_END);
    gtk_widget_set_margin_top(labelFrameBox1, FRAME_LABEL_MARGIN_TOP);
    gtk_widget_set_margin_bottom(labelFrameBox1, FRAME_LABEL_MARGIN_BOTTOM);

    // Making container for a button
    GtkWidget *boxCalcButton = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(box1), boxCalcButton, FALSE, FALSE, 0);

    gtk_widget_set_margin_start(boxCalcButton, 50);
    gtk_widget_set_margin_end(boxCalcButton, 50);
    gtk_widget_set_margin_top(boxCalcButton, 0);
    gtk_widget_set_margin_bottom(boxCalcButton, 0);

    // Making button "Calculate"
    GtkWidget *calcButton = gtk_button_new_with_label("Calculate");
    gtk_container_set_border_width(GTK_CONTAINER(calcButton), 0);
    gtk_box_pack_start(GTK_BOX(boxCalcButton), calcButton, FALSE, FALSE, 0);
    g_signal_connect(calcButton, "clicked", G_CALLBACK(calcButtonClick), NULL);

    // Program version output
    GtkWidget *fillBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box1), fillBox, TRUE, TRUE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(fillBox), -1, 171);

    printVersion(box1);

    // ------------------ SECOND BOX ------------------

    // Create a vertical box to hold label and comboBoxInterface
    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, BOX_MARGIN);
    gtk_box_pack_start(GTK_BOX(main_box), box2, TRUE, TRUE, 0);

    // Create a horizontal box to hold the label and comboBoxInterface
    GtkWidget *boxComboBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box2), boxComboBox, FALSE, FALSE, 0);

    // Create the label for the combo box
    GtkWidget *labelComboBox = gtk_label_new("Select an interface: ");
    gtk_box_pack_start(GTK_BOX(boxComboBox), labelComboBox, FALSE, FALSE, 0);
    gtk_widget_set_margin_top(labelComboBox, 10);

    // Create the combo box
    GtkWidget *fixed                   = gtk_fixed_new();
    GtkComboBoxText *comboBoxInterface = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());
    gtk_box_pack_start(GTK_BOX(boxComboBox), fixed, TRUE, TRUE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(comboBoxInterface), COMBO_BOX_WIDTH, -1); // Width a comboBoxInterface
    gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(comboBoxInterface), 0, 0);            // Add a combo_box to fixed contener
    comboBoxAddOptions(comboBoxInterface);                                           // Add intefaces options to an interface

    gtk_widget_set_margin_start(fixed, 0);
    gtk_widget_set_margin_end(fixed, 10);
    gtk_widget_set_margin_top(fixed, 10);
    gtk_widget_set_margin_bottom(fixed, 0);

    g_signal_connect(comboBoxInterface, "changed", G_CALLBACK(onComboBoxInterface), NULL);

    // Frame "ip address"
    GtkWidget *frameInterfaceOutput = gtk_frame_new("Interface network properties");
    gtk_box_pack_start(GTK_BOX(box2), frameInterfaceOutput, TRUE, TRUE, 0);

    gtk_widget_set_margin_start(frameInterfaceOutput, 0);
    gtk_widget_set_margin_end(frameInterfaceOutput, 10);
    gtk_widget_set_margin_top(frameInterfaceOutput, 10);
    gtk_widget_set_margin_bottom(frameInterfaceOutput, 0);

    // Label for frame "ip address"
    labelFrameBox2 = gtk_label_new(blankOutput);
    gtk_label_set_xalign(GTK_LABEL(labelFrameBox2), 0.0);
    gtk_container_add(GTK_CONTAINER(frameInterfaceOutput), labelFrameBox2);

    gtk_widget_set_margin_start(labelFrameBox2, FRAME_LABEL_MARGIN_START);
    gtk_widget_set_margin_end(labelFrameBox2, FRAME_LABEL_MARGIN_END);
    gtk_widget_set_margin_top(labelFrameBox2, FRAME_LABEL_MARGIN_TOP);
    gtk_widget_set_margin_bottom(labelFrameBox2, FRAME_LABEL_MARGIN_BOTTOM);

    // Frame for additional output for interface
    GtkWidget *frameInterfaceConfigOutput = gtk_frame_new("Interface config");
    gtk_box_pack_start(GTK_BOX(box2), frameInterfaceConfigOutput, TRUE, TRUE, 0);

    gtk_widget_set_margin_start(frameInterfaceConfigOutput, 0);
    gtk_widget_set_margin_end(frameInterfaceConfigOutput, 10);
    gtk_widget_set_margin_top(frameInterfaceConfigOutput, 0);
    gtk_widget_set_margin_bottom(frameInterfaceConfigOutput, 0);

    // Label for additional output for interface
    labelFrameInterfaceConfigOutput = gtk_label_new(blankOutputInterface);
    gtk_label_set_xalign(GTK_LABEL(labelFrameInterfaceConfigOutput), 0.0);
    gtk_container_add(GTK_CONTAINER(frameInterfaceConfigOutput), labelFrameInterfaceConfigOutput);

    gtk_widget_set_margin_start(labelFrameInterfaceConfigOutput, FRAME_LABEL_MARGIN_START);
    gtk_widget_set_margin_end(labelFrameInterfaceConfigOutput, FRAME_LABEL_MARGIN_END);
    gtk_widget_set_margin_top(labelFrameInterfaceConfigOutput, FRAME_LABEL_MARGIN_TOP);
    gtk_widget_set_margin_bottom(labelFrameInterfaceConfigOutput, FRAME_LABEL_MARGIN_BOTTOM);

    // Frame DNS configuration
    GtkWidget *frameFrameDnsConfig = gtk_frame_new("DNS configuration");
    gtk_box_pack_start(GTK_BOX(box2), frameFrameDnsConfig, TRUE, TRUE, 0);

    gtk_widget_set_margin_start(frameFrameDnsConfig, 0);
    gtk_widget_set_margin_end(frameFrameDnsConfig, 10);
    gtk_widget_set_margin_top(frameFrameDnsConfig, 0);
    gtk_widget_set_margin_bottom(frameFrameDnsConfig, 10);

    labelFrameDnsConfig = gtk_label_new(blankOutputDnsConfig);
    gtk_label_set_xalign(GTK_LABEL(labelFrameDnsConfig), 0.0);
    gtk_container_add(GTK_CONTAINER(frameFrameDnsConfig), labelFrameDnsConfig);

    gtk_widget_set_margin_start(labelFrameDnsConfig, FRAME_LABEL_MARGIN_START);
    gtk_widget_set_margin_top(labelFrameDnsConfig, FRAME_LABEL_MARGIN_TOP);
    gtk_widget_set_margin_bottom(labelFrameDnsConfig, FRAME_LABEL_MARGIN_BOTTOM);

    // ------------------ SET FONT FOR OUTPUTS ------------------

    setLabelOutputFont(labelFrameBox1, FONT_STYLE, FONT_OUTPUT_SIZE);
    setLabelOutputFont(labelFrameBox2, FONT_STYLE, FONT_OUTPUT_SIZE);
    setLabelOutputFont(labelFrameInterfaceConfigOutput, FONT_STYLE, FONT_OUTPUT_SIZE);
    setLabelOutputFont(labelFrameDnsConfig, FONT_STYLE, FONT_OUTPUT_SIZE);

    gtk_widget_show_all(window);
    gtk_main();
}
