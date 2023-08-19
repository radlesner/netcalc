#include "headers/outputs.h"
#include "headers/ipOperations.h"
#include "headers/netInterfaces.h"
#include "headers/segmentForOctet.h"

// -------------------------------------------------------------
void mainOutput(unsigned int ipAddrTab[4], unsigned int rawMaskPrefix)
{
    unsigned int ipMaskTab[4]      = {0, 0, 0, 0};
    unsigned int ipWildTab[4]      = {0, 0, 0, 0};
    unsigned int ipNetAddrTab[4]   = {0, 0, 0, 0};
    unsigned int ipBroadAddrTab[4] = {0, 0, 0, 0};
    unsigned int ipFirstHost[4]    = {0, 0, 0, 0};
    unsigned int ipLastHost[4]     = {0, 0, 0, 0};
    unsigned long int numHost;

    /*
        The following void functions perform calculations related to IP addresses
        and modify the values in the arrays of the parent function.

        NOTE: The void functions in this code change values directly in memory
        parent function arrays.

        Arrays in the code always have the abbreviation "Tab" at the end of the name
    */

    // --------------------------------------- Get the values to output
    getMask(ipMaskTab, rawMaskPrefix);
    getWildAddr(ipWildTab, ipMaskTab);
    getNetworkAddr(ipNetAddrTab, ipAddrTab, ipMaskTab);
    getBroadAddr(ipBroadAddrTab, ipNetAddrTab, ipMaskTab);
    getFirstLastHost(ipFirstHost, ipLastHost, ipNetAddrTab, ipBroadAddrTab);
    numHost = getHostNumber(rawMaskPrefix);

    // --------------------------------------- Print output
    printf("       IP address: %d.%d.%d.%d\n", ipAddrTab[0], ipAddrTab[1], ipAddrTab[2], ipAddrTab[3]);
    printf("     Mask address: %d.%d.%d.%d\n", ipMaskTab[0], ipMaskTab[1], ipMaskTab[2], ipMaskTab[3]);
    printf(" Wildcard address: %d.%d.%d.%d\n", ipWildTab[0], ipWildTab[1], ipWildTab[2], ipWildTab[3]);
    printf("  Network address: %d.%d.%d.%d/%d\n", ipNetAddrTab[0], ipNetAddrTab[1], ipNetAddrTab[2], ipNetAddrTab[3], rawMaskPrefix);
    printf("Broadcast address: %d.%d.%d.%d\n", ipBroadAddrTab[0], ipBroadAddrTab[1], ipBroadAddrTab[2], ipBroadAddrTab[3]);
    printf("     Firt address: %d.%d.%d.%d\n", ipFirstHost[0], ipFirstHost[1], ipFirstHost[2], ipFirstHost[3]);
    printf("     Last address: %d.%d.%d.%d\n", ipLastHost[0], ipLastHost[1], ipLastHost[2], ipLastHost[3]);
    printf("  Number of hosts: %ld\n", numHost);
}

// -------------------------------------------------------------
void additionalInterfaceOutput(char *interfaceName)
{
    char dhcpOutput[7];
    char macAddressOutput[18];
    char gatewayAddrOutput[17];
    char dnsAddrOutput[4][17];

    unsigned int ipGatewayAddrTab[4] = {0, 0, 0, 0};
    unsigned int ipDnsAddrTab[4][4]  = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    size_t sizeDnsOutput             = sizeof(ipDnsAddrTab) / sizeof(ipDnsAddrTab[0]);

    /*
        The following void functions perform calculations related to IP addresses
        and modify the values in the arrays of the parent function.

        NOTE: The void functions in this code change values directly in memory
        parent function arrays.

        Arrays in the code always have the abbreviation "Tab" at the end of the name
    */

    // --------------------------------------- Get the values to output
    getMacAddress(macAddressOutput, interfaceName);
    if (strcmp(interfaceName, "lo"))
    {
        getGatewayAddr(ipGatewayAddrTab, interfaceName);
        getDnsAddress(ipDnsAddrTab, interfaceName);
    }

    // --------------------------------------- Check output
    if (isDhcpConfig(interfaceName))
        sprintf(dhcpOutput, "DHCP");
    else
        sprintf(dhcpOutput, "Static");

    if (!ipcmp(ipGatewayAddrTab, 0, 0, 0, 0))
        sprintf(gatewayAddrOutput, "%d.%d.%d.%d", ipGatewayAddrTab[0], ipGatewayAddrTab[1], ipGatewayAddrTab[2], ipGatewayAddrTab[3]);
    else
        sprintf(gatewayAddrOutput, "Not configured");

    for (size_t i = 0; i < sizeDnsOutput; i++)
    {
        if (!ipcmp(ipDnsAddrTab[i], 0, 0, 0, 0))
            sprintf(dnsAddrOutput[i], "%d.%d.%d.%d", ipDnsAddrTab[0][0], ipDnsAddrTab[0][1], ipDnsAddrTab[0][2], ipDnsAddrTab[0][3]);
        else
            sprintf(dnsAddrOutput[i], "Not configured");
    }

    // --------------------------------------- Print output
    printf("\n");
    printf("    Configuration: %s\n", dhcpOutput);
    printf("      MAC address: %s\n", macAddressOutput);
    printf("  Gateway address: %s\n\n", gatewayAddrOutput);

    printf("            DNS 1: %s\n", dnsAddrOutput[0]);
    printf("            DNS 2: %s\n", dnsAddrOutput[1]);
    printf("            DNS 3: %s\n", dnsAddrOutput[2]);
    printf("            DNS 4: %s\n", dnsAddrOutput[3]);
}

// -------------------------------------------------------------
void helpOutput(void)
{
    printf("Usage: netcalc [ip_v4_address] [prefix_netmask]\n");
    printf("Netcalc with no arguments will launch a GTK window\n\n");

    printf("Options:\n");
    printf("    -i    --inteface      Calculates values from interface\n");
    printf("    -v    --version       Version program\n");
    printf("    -h    --help          Help panel\n");
}
