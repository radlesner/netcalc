#include "headers/outputs.h"
#include "headers/ipOperations.h"
#include "headers/netInterfaces.h"
#include "headers/segmentForOctet.h"

// -------------------------------------------------------------
void mainOutput(unsigned int *ipAddrTab, unsigned int rawMaskPrefix)
{
    // Value arrays
    unsigned int ipMaskTab[4]      = {0, 0, 0, 0};
    unsigned int ipWildTab[4]      = {0, 0, 0, 0};
    unsigned int ipNetAddrTab[4]   = {0, 0, 0, 0};
    unsigned int ipBroadAddrTab[4] = {0, 0, 0, 0};
    unsigned int ipFirstHost[4]    = {0, 0, 0, 0};
    unsigned int ipLastHost[4]     = {0, 0, 0, 0};
    unsigned long int numHost      = getHostNumber(rawMaskPrefix);

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
    // Output strings
    char dhcpOutput[7];
    char macAddressOutput[18];
    char gatewayAddrOutput[17];
    char dnsAddrOutput[4][17];
    char dnsResolver[32];

    // Value arrays
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
        getDnsAddress(ipDnsAddrTab, dnsResolver, interfaceName);
    }
    else
        sprintf(dnsResolver, "Not set");

    // --------------------------------------- Check output
    if (isDhcpConfig(interfaceName))
        sprintf(dhcpOutput, "DHCP");
    else
        sprintf(dhcpOutput, "Static");

    if (!ipcmp(ipGatewayAddrTab, 0, 0, 0, 0))
        sprintf(gatewayAddrOutput, "%d.%d.%d.%d", ipGatewayAddrTab[0], ipGatewayAddrTab[1], ipGatewayAddrTab[2], ipGatewayAddrTab[3]);
    else
        sprintf(gatewayAddrOutput, "Not set");

    for (size_t i = 0; i < sizeDnsOutput; i++)
    {
        if (!ipcmp(ipDnsAddrTab[i], 0, 0, 0, 0))
            sprintf(dnsAddrOutput[i], "%d.%d.%d.%d", ipDnsAddrTab[i][0], ipDnsAddrTab[i][1], ipDnsAddrTab[i][2], ipDnsAddrTab[i][3]);
        else
            sprintf(dnsAddrOutput[i], "Not set");
    }

    // --------------------------------------- Print output
    printf("\n");
    printf("    Configuration: %s\n", dhcpOutput);
    printf("      MAC address: %s\n", macAddressOutput);
    printf("  Gateway address: %s\n\n", gatewayAddrOutput);

    printf("              DNS: %s\n", dnsResolver);
    printf("    DNS address 1: %s\n", dnsAddrOutput[0]);
    printf("    DNS address 2: %s\n", dnsAddrOutput[1]);
    printf("    DNS address 3: %s\n", dnsAddrOutput[2]);
    printf("    DNS address 4: %s\n", dnsAddrOutput[3]);
}

// -------------------------------------------------------------
_Noreturn void helpOutput(void)
{
    printf("Usage example: netcalc -c 192.168.0.1 24\n");
    printf("Netcalc with no arguments will launch a GTK window\n\n");

    printf("Options:\n");
    printf("    -c    --calculator    Calculates values from command arguments\n");
    printf("    -i    --inteface      Calculates values from network interface\n");
    printf("    -v    --version       Version program\n");
    printf("    -h    --help          Help panel\n");

    exit(0);
}

_Noreturn void invalidArgumentsOutput(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (argc == 2)
        {
            printf("Unknown option: %s\n", argv[i]);
        }
        else
        {
            if (i == 1)
            {
                printf("Unknown options: %s", argv[i]);
            }
            else
            {
                printf(", %s", argv[i]);
            }

            if (i == (argc - 1))
            {
                printf("\n");
            }
        }
    }

    exit(0);
}
