#include "headers/gtkOutputSignals.h"
#include "../headers/ipOperations.h"
#include "../headers/netInterfaces.h"
#include "../headers/segmentForOctet.h"
#include "../headers/validArguments.h"
#include "headers/gtkMain.h"

extern GtkWidget *entryIpAddress;
extern GtkWidget *entryMaskPrefix;

extern GtkWidget *labelFrameBox1;
extern GtkWidget *labelFrameBox2;

void onComboBoxInterface(GtkComboBox *widget)
{
    GtkComboBoxText *comboBoxInterface = GTK_COMBO_BOX_TEXT(widget);
    gchar *selected_text               = gtk_combo_box_text_get_active_text(comboBoxInterface);
    unsigned int ipAddrTab[4]          = {0, 0, 0, 0};
    unsigned int ipMaskTab[4]          = {0, 0, 0, 0};
    unsigned int ipWildTab[4]          = {0, 0, 0, 0};
    unsigned int ipNetAddrTab[4]       = {0, 0, 0, 0};
    unsigned int ipBroadAddrTab[4]     = {0, 0, 0, 0};
    unsigned int ipFirstHost[4]        = {0, 0, 0, 0};
    unsigned int ipLastHost[4]         = {0, 0, 0, 0};
    unsigned int numHost;
    int maskPrefix;
    char result_text[1024];

    g_print("Selected interface: %s\n", selected_text);

    getInterfaceInfo(selected_text, ipAddrTab, ipMaskTab);
    maskPrefix = maskToPrefix(ipMaskTab);

    /*
        The following void functions perform calculations related to IP addresses
        and modify the values in the arrays of the parent function.

        NOTE: The void functions in this code change values directly in memory
        parent function arrays.

        Arrays in the code always have the abbreviation "Tab" at the end of the name
    */

    getWildAddr(ipWildTab, ipMaskTab);
    getNetworkAddr(ipNetAddrTab, ipAddrTab, ipMaskTab);
    getBroadAddr(ipBroadAddrTab, ipNetAddrTab, ipMaskTab);
    getFirstLastHost(ipFirstHost, ipLastHost, ipNetAddrTab, ipBroadAddrTab);
    numHost = getHostNumber(maskPrefix);

    sprintf(result_text,
            " IP address.......: %d.%d.%d.%d\n"
            " Mask address.....: %d.%d.%d.%d\n"
            " Wildcard address.: %d.%d.%d.%d\n"
            " Network address..: %d.%d.%d.%d/%d\n"
            " Broadcast address: %d.%d.%d.%d\n"
            " First address....: %d.%d.%d.%d\n"
            " Last address.....: %d.%d.%d.%d\n"
            " Number of hosts..: %d",
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

    gtk_label_set_text(GTK_LABEL(labelFrameBox2), result_text);
}

void calcButtonClick(void)
{
    const char *ip_address = gtk_entry_get_text(GTK_ENTRY(entryIpAddress));
    const char *maskPrefix = gtk_entry_get_text(GTK_ENTRY(entryMaskPrefix));

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
        /*
            The following void functions perform calculations related to IP addresses
            and modify the values in the arrays of the parent function.

            NOTE: The void functions in this code change values directly in memory
            parent function arrays.

            Arrays in the code always have the abbreviation "Tab" at the end of the name
        */

        getOctet(ipAddrTab, ip_address);
        getMask(ipMaskTab, atoi(maskPrefix));
        getWildAddr(ipWildTab, ipMaskTab);
        getNetworkAddr(ipNetAddrTab, ipAddrTab, ipMaskTab);
        getBroadAddr(ipBroadAddrTab, ipNetAddrTab, ipMaskTab);
        getFirstLastHost(ipFirstHost, ipLastHost, ipNetAddrTab, ipBroadAddrTab);
        numHost = getHostNumber(atoi(maskPrefix));

        sprintf(result_text,
                " IP address.......: %d.%d.%d.%d\n"
                " Mask address.....: %d.%d.%d.%d\n"
                " Wildcard address.: %d.%d.%d.%d\n"
                " Network address..: %d.%d.%d.%d/%s\n"
                " Broadcast address: %d.%d.%d.%d\n"
                " First address....: %d.%d.%d.%d\n"
                " Last address.....: %d.%d.%d.%d\n"
                " Number of hosts..: %d",
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

        gtk_label_set_text(GTK_LABEL(labelFrameBox1), result_text);
    }
    else
    {
        sprintf(result_text,
                " IP address.......: BAD IP ADDRESS OR MASK PREFIX\n"
                " Mask address.....:\n"
                " Wildcard address.:\n"
                " Network address..:\n"
                " Broadcast address:\n"
                " First address....:\n"
                " Last address.....:\n"
                " Number of hosts..:");

        gtk_label_set_text(GTK_LABEL(labelFrameBox1), result_text);
    }

    g_print("Calculate button clicked!\n");
}