#include "headers/netInterfaces.h"
#include "headers/commands.h"
#include "headers/ipOperations.h"
#include "headers/outputs.h"
#include "headers/segmentForOctet.h"

// -------------------------------------------------------------
int maskToPrefix(unsigned int *maskAddr)
{
    int prefix = 0;
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 7; j >= 0; j--)
        {
            if ((maskAddr[i] >> j) & 1)
                prefix++;
            else
                break;
        }
    }

    return prefix;
}

// -------------------------------------------------------------
void getInterfaceInfo(char *interfaceName, unsigned int *ipAddr, unsigned int *ipMask)
{
    struct ifaddrs *ifaddr, *ifa;
    struct sockaddr_in *buffer;

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
            // Getting IP address of interface
            buffer = (struct sockaddr_in *)ifa->ifa_addr;
            inet_ntop(AF_INET, &(buffer->sin_addr), ipAddress, INET_ADDRSTRLEN);

            // Getting subnet mask of interface
            buffer = (struct sockaddr_in *)ifa->ifa_netmask;
            inet_ntop(AF_INET, &(buffer->sin_addr), maskAddress, INET_ADDRSTRLEN);

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
                freeifaddrs(ifaddr);
                return true;
            }
        }
    }

    freeifaddrs(ifaddr);
    return false;
}

// -------------------------------------------------------------
void getMacAddress(char *macAddress, char *interfaceName)
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
void getGatewayAddr(unsigned int *ipGatewayAddr, char *interfaceName)
{
    char command[512];
    char cmdResult[512] = "";
    unsigned int decimalIP;

    snprintf(command,
             sizeof(command),
             "awk -v interface=\"%s\" '$1 == interface && $2 == \"00000000\" {gsub(/../, \"0x&\",$3); sub(/^0x/, \"\", "
             "$3); gsub(/0x/, \"\", $3); print $3}' "
             "/proc/net/route",
             interfaceName);

    getCommandResult(cmdResult, command);

    sscanf(cmdResult, "%x", &decimalIP); // Convert HEX to DEC
    ipGatewayAddr[3] = (decimalIP >> 24) & 0xFF;
    ipGatewayAddr[2] = (decimalIP >> 16) & 0xFF;
    ipGatewayAddr[1] = (decimalIP >> 8) & 0xFF;
    ipGatewayAddr[0] = decimalIP & 0xFF;
}

// -------------------------------------------------------------
int isDhcpConfig(const char *interface)
{
    char command[64];
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
void getDnsAddress(unsigned int ipDnsAddrTab[4][4], char *dnsResolver, char *interfaceName)
{
    char command[128];
    char cmdResult[128]      = "";
    char strIpDnsAddr[4][15] = {{""}, {""}, {""}, {""}};

    sprintf(command, "grep -w 'nameserver' /etc/resolv.conf | awk '{print $2}'");
    getCommandResult(cmdResult, command);
    getOctet(ipDnsAddrTab[0], cmdResult);
    sprintf(dnsResolver, "/etc/resolv.conf");

    if (ipcmp(ipDnsAddrTab[0], 127, 0, 0, 53))
    {
        memset(cmdResult, 0, sizeof(cmdResult));
        sprintf(command, "nmcli device show %s | grep -w 'IP4.DNS' | awk '{print $2}'", interfaceName);
        sprintf(dnsResolver, "systemd-resolved");
        getCommandResult(cmdResult, command);
    }

    int newlineCount = 0;
    int y            = 0; // New line buffer index
    int x            = 0; // Line index
    char buffer[64]  = "";

    for (size_t i = 0; i < strlen(cmdResult); i++)
    {
        if (cmdResult[i] == '\n')
        {
            strcpy(strIpDnsAddr[x], buffer);
            getOctet(ipDnsAddrTab[x], strIpDnsAddr[x]);
            memset(buffer, 0, sizeof(buffer));

            newlineCount++;
            y = 0;
            x++;
        }
        else
        {
            buffer[y] = cmdResult[i];
            y++;
        }
    }
}
