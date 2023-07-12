#include "headers/outputs.h"
#include "headers/ipOperations.h"
#include "headers/segmentForOctet.h"

void mainOutput(const char *rawIpAddr, unsigned int rawMaskPrefix)
{
    unsigned int ipAddrTab[4]      = {0, 0, 0, 0};
    unsigned int ipMaskTab[4]      = {0, 0, 0, 0};
    unsigned int ipWildTab[4]      = {0, 0, 0, 0};
    unsigned int ipNetAddrTab[4]   = {0, 0, 0, 0};
    unsigned int ipBroadAddrTab[4] = {0, 0, 0, 0};
    unsigned int ipFirstHost[4]    = {0, 0, 0, 0};
    unsigned int ipLastHost[4]     = {0, 0, 0, 0};
    unsigned int numHost;

    getOctet(ipAddrTab, rawIpAddr);
    getMask(ipMaskTab, rawMaskPrefix);
    getWildAddr(ipWildTab, ipMaskTab);
    getNetworkAddr(ipNetAddrTab, ipAddrTab, ipMaskTab);
    getBroadAddr(ipBroadAddrTab, ipNetAddrTab, ipMaskTab);
    getFirstLastHost(ipFirstHost, ipLastHost, ipNetAddrTab, ipBroadAddrTab);
    numHost = getHostNumber(rawMaskPrefix);

    // Output for console
    printf("       IP address: %d.%d.%d.%d\n", ipAddrTab[0], ipAddrTab[1], ipAddrTab[2], ipAddrTab[3]);
    printf("\n");
    printf("     Mask address: %d.%d.%d.%d\n", ipMaskTab[0], ipMaskTab[1], ipMaskTab[2], ipMaskTab[3]);
    printf(" Wildcard address: %d.%d.%d.%d\n", ipWildTab[0], ipWildTab[1], ipWildTab[2], ipWildTab[3]);
    printf("\n");
    printf("  Network address: %d.%d.%d.%d/%d\n", ipNetAddrTab[0], ipNetAddrTab[1], ipNetAddrTab[2], ipNetAddrTab[3], rawMaskPrefix);
    printf("Broadcast address: %d.%d.%d.%d\n", ipBroadAddrTab[0], ipBroadAddrTab[1], ipBroadAddrTab[2], ipBroadAddrTab[3]);
    printf("     Firt address: %d.%d.%d.%d\n", ipFirstHost[0], ipFirstHost[1], ipFirstHost[2], ipFirstHost[3]);
    printf("     Last address: %d.%d.%d.%d\n", ipLastHost[0], ipLastHost[1], ipLastHost[2], ipLastHost[3]);
    printf("  Number of hosts: %d\n", numHost);
}

void helpOutput()
{
    printf("Usage: netcalc [ip_v4_address] [prefix_netmask]\n");
    printf("Options:\n");
    printf("    -i    --inteface    Calculates values from interface\n");
    printf("    -v    --version     Version program\n");
    printf("    -h    --help        Help panel\n");
}