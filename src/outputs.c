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

    getMask(ipMaskTab, rawMaskPrefix);
    getWildAddr(ipWildTab, ipMaskTab);
    getNetworkAddr(ipNetAddrTab, ipAddrTab, ipMaskTab);
    getBroadAddr(ipBroadAddrTab, ipNetAddrTab, ipMaskTab);
    getFirstLastHost(ipFirstHost, ipLastHost, ipNetAddrTab, ipBroadAddrTab);
    numHost = getHostNumber(rawMaskPrefix);

    // Output for console
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
    char dhcp[7];
    char macAddress[18];
    unsigned int ipGatewayAddrTab[4] = {0, 0, 0, 0};
    char ipDnsAddrTab[4][64]         = {{""}, {""}, {""}, {""}};

    /*
        The following void functions perform calculations related to IP addresses
        and modify the values in the arrays of the parent function.

        NOTE: The void functions in this code change values directly in memory
        parent function arrays.

        Arrays in the code always have the abbreviation "Tab" at the end of the name
    */

    getMacAddress(macAddress, interfaceName);
    if (strcmp(interfaceName, "lo"))
    {
        getGatewayAddr(ipGatewayAddrTab, interfaceName);
        getDnsAddress(ipDnsAddrTab, interfaceName);
    }

    printf("\n");

    if (isDhcpConfig(interfaceName))
        sprintf(dhcp, "DHCP");
    else
        sprintf(dhcp, "Static");

    printf("    Configuration: %s\n", dhcp);
    printf("      MAC address: %s\n", macAddress);
    printf("  Gateway address: %d.%d.%d.%d\n\n", ipGatewayAddrTab[0], ipGatewayAddrTab[1], ipGatewayAddrTab[2], ipGatewayAddrTab[3]);

    printf("            DNS 1: %s\n", ipDnsAddrTab[0]);
    printf("            DNS 2: %s\n", ipDnsAddrTab[1]);
    printf("            DNS 3: %s\n", ipDnsAddrTab[2]);
    printf("            DNS 4: %s\n", ipDnsAddrTab[3]);
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
