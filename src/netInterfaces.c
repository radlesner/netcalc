#include "headers/netInterfaces.h"
#include "headers/outputs.h"
#include "headers/segmentForOctet.h"

#define COMMAND_GATEWAY_ADDRESS "awk -v interface=\"%s\" '$1 == interface && $2 == \"00000000\" {gsub(/../, \"0x&\",$3); sub(/^0x/, \"\", $3); gsub(/0x/, \"\", $3); print $3}' /proc/net/route"

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
        if (ifa->ifa_addr == NULL)
            continue;

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
        if (!ifa->ifa_addr)
            continue;
        if (ifa->ifa_addr->sa_family == AF_INET)
            printf("> %s\n", ifa->ifa_name);
    }
    if (ifaddr != NULL)
        freeifaddrs(ifaddr);
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
        if (!ifa->ifa_addr)
            continue;

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

// -------------------------------------------------------------
void getMacAddress(char macAddress[], char *interfaceName)
{
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__) || defined(__ghostbsd__)

    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        if (ifa->ifa_addr->sa_family == AF_LINK)
        {
            struct sockaddr_dl *sdl = (struct sockaddr_dl *)ifa->ifa_addr;
            unsigned char *mac      = (unsigned char *)LLADDR(sdl);

            if (strcmp(interfaceName, ifa->ifa_name) == 0)
                snprintf(macAddress, 18, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        }
    }

    freeifaddrs(ifaddr);
    return;

#define BSD_SYSTEM
#else

    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        if (ifa->ifa_addr->sa_family == AF_PACKET)
        {
            struct sockaddr_ll *s = (struct sockaddr_ll *)ifa->ifa_addr;
            unsigned char *mac    = s->sll_addr;

            if (!strcmp(interfaceName, ifa->ifa_name))
                snprintf(macAddress, 18, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        }
    }

    freeifaddrs(ifaddr);
    return;

#define OTHER_SYSTEM
#endif
}

// -------------------------------------------------------------
void getGatewayAddr(unsigned int ipGatewayAddr[], char *interfaceName)
{
    char command[512];
    char result[512];

    unsigned int decimalIP;

    FILE *fp;

    snprintf(command, sizeof(command), COMMAND_GATEWAY_ADDRESS, interfaceName);

    fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    if (fgets(result, sizeof(result), fp) != NULL)
    {
        sscanf(result, "%x", &decimalIP); // Convert HEX to DEC

        ipGatewayAddr[3] = (decimalIP >> 24) & 0xFF;
        ipGatewayAddr[2] = (decimalIP >> 16) & 0xFF;
        ipGatewayAddr[1] = (decimalIP >> 8) & 0xFF;
        ipGatewayAddr[0] = decimalIP & 0xFF;
    }

    pclose(fp);

    return;
}

// -------------------------------------------------------------
int isStaticInterface(const char *interface)
{
    char command[22];
    sprintf(command, "ip -o -4 addr show %s", interface);

    FILE *fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("popen");
        return -1;
    }

    char buffer[256];
    int is_static = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (strstr(buffer, "dynamic") == NULL)
        {
            is_static = 1;
            break;
        }
    }

    pclose(fp);
    return is_static;
}
