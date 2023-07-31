#include "headers/netInterfaces.h"
#include "headers/outputs.h"
#include "headers/segmentForOctet.h"

// -------------------------------------------------------------
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

// -------------------------------------------------------------
void getInterfaceInfo(char *interfaceName, unsigned int ipAddr[], unsigned int ipMask[])
{
    struct ifaddrs *ifaddr, *ifa;
    struct sockaddr_in *sockAddrBuffer;

    char ipAddress[INET_ADDRSTRLEN];
    char maskAddress[INET_ADDRSTRLEN];

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
            // Get IP address
            sockAddrBuffer = (struct sockaddr_in *)ifa->ifa_addr;
            inet_ntop(AF_INET, &(sockAddrBuffer->sin_addr), ipAddress, INET_ADDRSTRLEN);

            // Get Mask
            sockAddrBuffer = (struct sockaddr_in *)ifa->ifa_netmask;
            inet_ntop(AF_INET, &(sockAddrBuffer->sin_addr), maskAddress, INET_ADDRSTRLEN);

            if (!strcmp(interfaceName, ifa->ifa_name))
            {
                getOctet(ipAddr, ipAddress);
                getOctet(ipMask, maskAddress);

                break;
            }
        }
    }

    freeifaddrs(ifaddr);
}

// -------------------------------------------------------------
void showInterfaces(void)
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

// -------------------------------------------------------------
bool isExistInterface(char *interfaceName)
{
    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        exit(1);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr) continue;

        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            if (!strcmp(interfaceName, ifa->ifa_name))
            {
                return true;
                break;
            }
        }
    }

    return false;
}
