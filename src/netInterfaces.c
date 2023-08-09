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
#ifdef BSD_SYSTEM
    char command[256];
    snprintf(command, sizeof(command), "ifconfig %s | grep -Eo '([0-9A-Fa-f]{2}:){5}([0-9A-Fa-f]{2})'", interfaceName);

    if (!strcmp(interfaceName, "lo0"))
    {
        sprintf(macAddress, "00:00:00:00:00:00");
        return;
    }

    getCommandResult(macAddress, command);
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
#endif
}

// -------------------------------------------------------------
void getGatewayAddr(unsigned int ipGatewayAddr[], char *interfaceName)
{
#ifdef BSD_SYSTEM
    return;
#else
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
#endif
}

// -------------------------------------------------------------
int isDhcpConfig(const char *interface)
{
#ifdef BSD_SYSTEM
    return -1;
#else
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
#endif
}

// -------------------------------------------------------------
void getDnsAddress(unsigned int ipDnsAddrTab[])
{
    char command[128];
    char cmdResult[256];

    if (isSDBUSavailable())
    {
        getSDBUS_dns_IP_address(ipDnsAddrTab);
    }
    else
    {
        sprintf(command, "grep -w -m 1 'nameserver' /etc/resolv.conf | awk '{print $2}'");
        getCommandResult(cmdResult, command);
        getOctet(ipDnsAddrTab, cmdResult);
    }
}

// -------------------------------------------------------------
int isSDBUSavailable(void)
{
    sd_bus_error dbusErr = SD_BUS_ERROR_NULL;
    sd_bus_message *msg  = NULL;
    sd_bus *dbus         = NULL;

    int err = sd_bus_open_system(&dbus);
    if (err < 0)
    {
        // fprintf(stderr, "can't connect to system D-Bus: %s\n", strerror(-err));
        return 0;
    }

    err = sd_bus_get_property(dbus, "org.freedesktop.resolve1", "/org/freedesktop/resolve1", "org.freedesktop.resolve1.Manager", "DNS", &dbusErr, &msg, "a(iiay)");
    if (err < 0)
    {
        // fprintf(stderr, "can't connect to systemd-resolved: %s\n", dbusErr.message);
        sd_bus_error_free(&dbusErr);
        sd_bus_unref(dbus);
        return 0;
    }

    err = sd_bus_message_enter_container(msg, SD_BUS_TYPE_ARRAY, "(iiay)");
    if (err < 0)
    {
        // fprintf(stderr, "error entering array container: %s\n", strerror(-err));
        sd_bus_message_unref(msg);
        sd_bus_unref(dbus);
        return 0;
    }

    sd_bus_message_exit_container(msg);
    sd_bus_message_unref(msg);
    sd_bus_unref(dbus);

    return 1;
}

// -------------------------------------------------------------
void getSDBUS_dns_IP_address(unsigned int ipDnsAddrTab[])
{
    sd_bus_message *msg = NULL;
    sd_bus *dbus        = NULL;

    int32_t netif;
    int32_t af;
    size_t n;
    const void *addr;
    char buf[64];
    int err;

    while (sd_bus_message_enter_container(msg, SD_BUS_TYPE_STRUCT, "iiay") > 0)
    {
        err = sd_bus_message_read(msg, "ii", &netif, &af);
        if (err < 0)
        {
            // fprintf(stderr, "error reading struct members: %s\n", strerror(-err));
            sd_bus_message_unref(msg);
            sd_bus_unref(dbus);
            return;
        }
        err = sd_bus_message_read_array(msg, 'y', &addr, &n);
        if (err < 0)
        {
            // fprintf(stderr, "error reading array: %s\n", strerror(-err));
            sd_bus_message_unref(msg);
            sd_bus_unref(dbus);
            return;
        }
        sd_bus_message_exit_container(msg);
        inet_ntop(af, addr, buf, sizeof(buf));

        // ----------------------------------- //
        getOctet(ipDnsAddrTab, buf);
    }
    sd_bus_message_exit_container(msg);

    sd_bus_message_unref(msg);
    sd_bus_unref(dbus);
}
