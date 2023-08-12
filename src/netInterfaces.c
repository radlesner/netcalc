#include "headers/netInterfaces.h"
#include "headers/commands.h"
#include "headers/ipOperations.h"
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
}

// -------------------------------------------------------------
void getGatewayAddr(unsigned int ipGatewayAddr[], char *interfaceName)
{
    char command[512];
    char result[512];
    unsigned int decimalIP;
    FILE *fp;

    snprintf(command,
             sizeof(command),
             "awk -v interface=\"%s\" '$1 == interface && $2 == \"00000000\""
             " {gsub(/../, \"0x&\",$3); sub(/^0x/, \"\", $3); gsub(/0x/, "
             "\"\", $3); print $3}' /proc/net/route",
             interfaceName);

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
int isDhcpConfig(const char *interface)
{
    char command[22];
    char buffer[256];
    int boolResult = 1; // default TRUE

    sprintf(command, "ip -o -4 addr show %s", interface);

    FILE *fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("popen");
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (strstr(buffer, "dynamic") == NULL)
        {
            boolResult = 0; // FALSE
            break;
        }
    }

    pclose(fp);
    return boolResult;
}

// -------------------------------------------------------------
void getDnsAddress(unsigned int ipDnsAddrTab[], char *interfaceName)
{
    char command[128];
    char cmdResult[256];

    sprintf(command, "grep -w -m 1 'nameserver' /etc/resolv.conf | awk '{print $2}'");
    getCommandResult(cmdResult, command);
    getOctet(ipDnsAddrTab, cmdResult);

    if (ipcmp(ipDnsAddrTab, 127, 0, 0, 53))
    {
        sprintf(command, "nmcli device show %s | grep -w -m 1 'IP4.DNS' | awk '{print $2}'", interfaceName);
        getCommandResult(cmdResult, command);
        getOctet(ipDnsAddrTab, cmdResult);
    }
}
