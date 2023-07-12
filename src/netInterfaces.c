#include "headers/netInterfaces.h"
#include "headers/outputs.h"
#include "headers/segmentForOctet.h"

int maskToPrefix(unsigned int maskAddr[])
{
    int prefix = 0;
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 7; j >= 0; j--)
        {
            if ((maskAddr[i] >> j) & 1)
            {
                prefix++;
            }
            else
            {
                break;
            }
        }
    }

    return prefix;
}

void getInterfaceInfo(char *interfaceName)
{
    struct ifaddrs *ifaddr, *ifa;
    struct sockaddr_in *addr, *netmask;

    char ip[INET_ADDRSTRLEN];
    char subnet[INET_ADDRSTRLEN];

    unsigned int ipAddr[4] = {0, 0, 0, 0};
    unsigned int ipMask[4] = {0, 0, 0, 0};
    int maskPrefix;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(1);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL) continue;

        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            addr = (struct sockaddr_in *)ifa->ifa_addr;
            inet_ntop(AF_INET, &(addr->sin_addr), ip, INET_ADDRSTRLEN);

            netmask = (struct sockaddr_in *)ifa->ifa_netmask;
            inet_ntop(AF_INET, &(netmask->sin_addr), subnet, INET_ADDRSTRLEN);

            char *currentInterfaceName = ifa->ifa_name;
            int result                 = strcmp(interfaceName, currentInterfaceName);

            if (result == 0)
            {
                getOctet(ipAddr, ip);
                getOctet(ipMask, subnet);
                maskPrefix = maskToPrefix(ipMask);
                mainOutput(ip, maskPrefix);
            }
        }
    }

    freeifaddrs(ifaddr);
}

void showInterfaces()
{
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(1);
    }

    printf("List of active interfaces\n");
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr) continue;
        if (ifa->ifa_addr->sa_family == AF_INET) printf("> %s\n", ifa->ifa_name);
    }
    if (ifaddr != NULL) freeifaddrs(ifaddr);
}