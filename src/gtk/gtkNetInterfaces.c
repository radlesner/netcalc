#include "headers/gtkNetInterfaces.h"
#include "../headers/segmentForOctet.h"

void gtkGetInterfaceInfo(char *interfaceName, unsigned int ipAddr[], unsigned int ipMask[])
{
    struct ifaddrs *ifaddr, *ifa;
    struct sockaddr_in *addr, *netmask;

    char ipAddrBuffer[INET_ADDRSTRLEN];
    char subnetAddrBuffer[INET_ADDRSTRLEN];

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
            inet_ntop(AF_INET, &(addr->sin_addr), ipAddrBuffer, INET_ADDRSTRLEN);

            netmask = (struct sockaddr_in *)ifa->ifa_netmask;
            inet_ntop(AF_INET, &(netmask->sin_addr), subnetAddrBuffer, INET_ADDRSTRLEN);

            if (!strcmp(interfaceName, ifa->ifa_name))
            {
                getOctet(ipAddr, ipAddrBuffer);
                getOctet(ipMask, subnetAddrBuffer);

                break;
            }
        }
    }

    freeifaddrs(ifaddr);
}