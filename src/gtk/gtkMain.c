#include "headers/gtkMain.h"
#include "headers/gtkOutputSignals.h"

#define WINDOW_RESIZABLE           FALSE
#define GTK_WINDOW_WIDTH           100
#define GTK_WINDOW_HEIGHT          100
#define BOX_MARGIN                 10
#define FONT_OUTPUT                "Monospace"
#define FONT_OUTPUT_SIZE           13
#define FONT_OUTPUT_VERSION_SIZE   10

#define FRAME_OUTPUT_MARGIN_START  10
#define FRAME_OUTPUT_MARGIN_END    10
#define FRAME_OUTPUT_MARGIN_TOP    10
#define FRAME_OUTPUT_MARGIN_BOTTOM 0

#define BUTTON_MARGIN_START        50
#define BUTTON_MARGIN_END          50
#define BUTTON_MARGIN_TOP          0
#define BUTTON_MARGIN_BOTTOM       10

#define COMBO_BOX_WIDTH            190
#define COMBO_BOX_MARGIN_START     0
#define COMBO_BOX_MARGIN_END       10
#define COMBO_BOX_MARGIN_TOP       10
#define COMBO_BOX_MARGIN_BOTTOM    0

GtkWidget *entryIpAddress;
GtkWidget *entryMaskPrefix;

GtkWidget *labelFrameBox1;
GtkWidget *labelFrameBox2;
GtkWidget *labelFrameInterfaceConfigOutput;

char blankOutput[160];
char blankOutputInterface[160];

// -------------------------------------------------------------
static void comboBoxAddOptions(GtkComboBoxText *comboBoxInterface)
{
    // Shows connected interfaces to combo box
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(1);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr)
            continue;
        if (ifa->ifa_addr->sa_family == AF_INET)
            gtk_combo_box_text_append_text(comboBoxInterface, ifa->ifa_name);
    }

    if (ifaddr != NULL)
        freeifaddrs(ifaddr);
}

// -------------------------------------------------------------
static void on_window_closed(void)
{
    g_print("Window closed\n");
    gtk_main_quit();
}

// -------------------------------------------------------------
static void setLabelOutputFont(GtkWidget *label, char *fontName, int fontSize)
{
    // Setting font for outputs addresses labels
    PangoFontDescription *fontGtkOutput = pango_font_description_new();
    pango_font_description_set_family(fontGtkOutput, fontName);
    pango_font_description_set_absolute_size(fontGtkOutput, fontSize * PANGO_SCALE);

    gchar *cssFontGtkOutput               = g_strdup_printf("* { font-family: \"%s\"; font-size: %dpx; }", pango_font_description_get_family(fontGtkOutput), (int)pango_font_description_get_size(fontGtkOutput) / PANGO_SCALE);
    GtkCssProvider *providerFontGtkOutput = gtk_css_provider_new();
    gtk_css_provider_load_from_data(providerFontGtkOutput, cssFontGtkOutput, -1, NULL);
    g_free(cssFontGtkOutput);

    gtk_style_context_add_provider(gtk_widget_get_style_context(label), GTK_STYLE_PROVIDER(providerFontGtkOutput), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(providerFontGtkOutput);
    pango_font_description_free(fontGtkOutput);
}

// --------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------- GTK MAIN --------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------
void gtkWindowInit(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    setlocale(LC_ALL, "");

    sprintf(blankOutput,
            " IP address.......:\n"
            " Mask address.....:\n"
            " Wildcard address.:\n"
            " Network address..:\n"
            " Broadcast address:\n"
            " First address....:\n"
            " Last address.....:\n"
            " Number of hosts..:");

    sprintf(blankOutputInterface,
            " Configuration.....:\n"
            " MAC address.......:\n"
            " Gateway address...:");

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
    gtk_label_set_xalign(GTK_LABEL(labelIpAddressBox1), 0.0);
    gtk_label_set_yalign(GTK_LABEL(labelIpAddressBox1), 0.5);

    // Making textbox "IP address"
    entryIpAddress = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryIpAddress), "Enter IP address");
    gtk_box_pack_start(GTK_BOX(fieldTextBox1), entryIpAddress, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entryIpAddress), 0.0);
    g_signal_connect(entryIpAddress, "activate", G_CALLBACK(calcButtonClick), NULL);

    // Making label "Subnet mask"
    GtkWidget *labelPrefixBox1 = gtk_label_new("  /  ");
    gtk_box_pack_start(GTK_BOX(fieldTextBox1), labelPrefixBox1, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(labelPrefixBox1), 0.0);
    gtk_label_set_yalign(GTK_LABEL(labelPrefixBox1), 0.5);

    // Making textbox "Subnet mask"
    entryMaskPrefix = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryMaskPrefix), "Enter mask prefix");
    gtk_box_pack_start(GTK_BOX(fieldTextBox1), entryMaskPrefix, FALSE, FALSE, 0);
    gtk_entry_set_alignment(GTK_ENTRY(entryMaskPrefix), 0.0);
    g_signal_connect(entryMaskPrefix, "activate", G_CALLBACK(calcButtonClick), NULL);

    // Frame "address address"
    GtkWidget *frameAddressOutput = gtk_frame_new("Network properties");
    gtk_box_pack_start(GTK_BOX(box1), frameAddressOutput, TRUE, TRUE, 0);
    gtk_widget_set_margin_start(frameAddressOutput, FRAME_OUTPUT_MARGIN_START);
    gtk_widget_set_margin_end(frameAddressOutput, FRAME_OUTPUT_MARGIN_END);
    gtk_widget_set_margin_bottom(frameAddressOutput, FRAME_OUTPUT_MARGIN_BOTTOM);

    // Label for frame "ip address"
    labelFrameBox1 = gtk_label_new(blankOutput);
    gtk_label_set_xalign(GTK_LABEL(labelFrameBox1), 0.0);
    gtk_container_add(GTK_CONTAINER(frameAddressOutput), labelFrameBox1);

    // Making container for a button
    GtkWidget *boxCalcButton = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(box1), boxCalcButton, FALSE, FALSE, 0);
    gtk_widget_set_margin_start(boxCalcButton, BUTTON_MARGIN_START);
    gtk_widget_set_margin_end(boxCalcButton, BUTTON_MARGIN_END);
    gtk_widget_set_margin_top(boxCalcButton, BUTTON_MARGIN_TOP);
    // gtk_widget_set_margin_bottom(boxCalcButton, 66);

    // Making button "Calculate"
    GtkWidget *calcButton = gtk_button_new_with_label("Calculate");
    gtk_container_set_border_width(GTK_CONTAINER(calcButton), 0);
    gtk_box_pack_start(GTK_BOX(boxCalcButton), calcButton, FALSE, FALSE, 0);
    g_signal_connect(calcButton, "clicked", G_CALLBACK(calcButtonClick), NULL);

    // Program version output
    GtkWidget *boxVersionProgramBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(box1), boxVersionProgramBox, TRUE, TRUE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(boxVersionProgramBox), -1, 42);
    gtk_widget_set_margin_start(boxVersionProgramBox, 2);

    char versionProgramOutput[24];
    sprintf(versionProgramOutput, "Netcalc v%s ", VERSION_PROGRAM);

    GtkWidget *labelVersionProgram = gtk_label_new(versionProgramOutput);
    gtk_container_add(GTK_CONTAINER(boxVersionProgramBox), labelVersionProgram);
    gtk_label_set_yalign(GTK_LABEL(labelVersionProgram), 1);

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
    gtk_label_set_xalign(GTK_LABEL(labelComboBox), 0.0);
    gtk_label_set_yalign(GTK_LABEL(labelComboBox), 0.7);

    // Create the combo box
    GtkWidget *fixed                   = gtk_fixed_new();
    GtkComboBoxText *comboBoxInterface = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());
    gtk_box_pack_start(GTK_BOX(boxComboBox), fixed, TRUE, TRUE, 0);
    gtk_widget_set_margin_start(fixed, COMBO_BOX_MARGIN_START);
    gtk_widget_set_margin_end(fixed, COMBO_BOX_MARGIN_END);
    gtk_widget_set_margin_top(fixed, COMBO_BOX_MARGIN_TOP);
    gtk_widget_set_margin_bottom(fixed, COMBO_BOX_MARGIN_BOTTOM);
    gtk_widget_set_size_request(GTK_WIDGET(comboBoxInterface), COMBO_BOX_WIDTH, -1); // Width a comboBoxInterface
    gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(comboBoxInterface), 0, 0);            // Add a combo_box to fixed contener
    comboBoxAddOptions(comboBoxInterface);                                           // Add intefaces options to an interface
    g_signal_connect(comboBoxInterface, "changed", G_CALLBACK(onComboBoxInterface), NULL);

    // Frame "ip address"
    GtkWidget *frameInterfaceOutput = gtk_frame_new("Interface network properties");
    gtk_box_pack_start(GTK_BOX(box2), frameInterfaceOutput, TRUE, TRUE, 0);
    gtk_widget_set_margin_start(frameInterfaceOutput, 0);
    gtk_widget_set_margin_end(frameInterfaceOutput, FRAME_OUTPUT_MARGIN_END);
    gtk_widget_set_margin_top(frameInterfaceOutput, FRAME_OUTPUT_MARGIN_TOP);
    gtk_widget_set_margin_bottom(frameInterfaceOutput, FRAME_OUTPUT_MARGIN_BOTTOM);
    gtk_widget_set_size_request(frameInterfaceOutput, -1, 180);

    // Label for frame "ip address"
    labelFrameBox2 = gtk_label_new(blankOutput);
    gtk_label_set_xalign(GTK_LABEL(labelFrameBox2), 0.0);
    gtk_container_add(GTK_CONTAINER(frameInterfaceOutput), labelFrameBox2);

    // Frame for additional output for interface
    GtkWidget *frameInterfaceConfigOutput = gtk_frame_new("Interface config");
    gtk_box_pack_start(GTK_BOX(box2), frameInterfaceConfigOutput, TRUE, TRUE, 0);
    gtk_widget_set_margin_start(frameInterfaceConfigOutput, 0);
    gtk_widget_set_margin_end(frameInterfaceConfigOutput, FRAME_OUTPUT_MARGIN_END);
    gtk_widget_set_margin_top(frameInterfaceConfigOutput, 0);
    gtk_widget_set_margin_bottom(frameInterfaceConfigOutput, 10);
    gtk_widget_set_size_request(frameInterfaceConfigOutput, -1, 90);

    // Label for additional output for interface
    labelFrameInterfaceConfigOutput = gtk_label_new(blankOutputInterface);
    gtk_label_set_xalign(GTK_LABEL(labelFrameInterfaceConfigOutput), 0.0);
    gtk_container_add(GTK_CONTAINER(frameInterfaceConfigOutput), labelFrameInterfaceConfigOutput);

    // ------------------ SET FONT FOR OUTPUTS ------------------

    setLabelOutputFont(labelFrameBox1, FONT_OUTPUT, FONT_OUTPUT_SIZE);
    setLabelOutputFont(labelFrameBox2, FONT_OUTPUT, FONT_OUTPUT_SIZE);
    setLabelOutputFont(labelFrameInterfaceConfigOutput, FONT_OUTPUT, FONT_OUTPUT_SIZE);
    setLabelOutputFont(labelVersionProgram, FONT_OUTPUT, FONT_OUTPUT_VERSION_SIZE);

    gtk_widget_show_all(window);
    gtk_main();
}
