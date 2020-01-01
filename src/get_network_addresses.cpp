#include "headers/get_network_addresses.h"

void get_network (char *interface_name)
{
    struct ifaddrs* ifAddrStruct = NULL;
    struct ifaddrs* ifa = NULL;
    void* tmpAddrPtr = NULL;

    int ip_octet[4],
        netmask_octet[4],
        netmask_prefix;

    std::string
        bin_ip_address,
        bin_netmask,
        bin_network,
        bin_broadcast;

    getifaddrs(&ifAddrStruct);

    for(ifa = ifAddrStruct;  ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr) continue;
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            char address_buffer[INET_ADDRSTRLEN];
            char mask_buffer[INET_ADDRSTRLEN];

            tmpAddrPtr = &((struct sockaddr_in *)(ifa->ifa_addr))->sin_addr;
            inet_ntop(AF_INET, tmpAddrPtr, address_buffer, INET_ADDRSTRLEN);

            tmpAddrPtr = &((struct sockaddr_in *)(ifa->ifa_netmask))->sin_addr;
            inet_ntop(AF_INET, tmpAddrPtr, mask_buffer, INET_ADDRSTRLEN);

            /*
                OUTPUT
            */

            if (static_cast<std::string>(ifa->ifa_name) == interface_name)
            {
                for (size_t i = 0; i < 4; i++)
                {
                    ip_octet[i] = std::stoi(division_on_octet(address_buffer, i));
                    netmask_octet[i] = std::stoi(division_on_octet(mask_buffer, i));

                    bin_ip_address += dec_to_bin(ip_octet[i]);
                    bin_netmask += dec_to_bin(netmask_octet[i]);
                }

                netmask_prefix = make_prefix(bin_netmask);

                std::cout
                    << "Interface:         " << ifa->ifa_name << std::endl
                    << "IP address:        " << address_buffer << std::endl
                    << "Netmask:           " << mask_buffer << std::endl;

                bin_network = get_network_address(bin_ip_address, bin_netmask);
                bin_broadcast = get_broadcast_addr(bin_network, bin_netmask);
                get_number_hosts(bin_ip_address, std::to_string(netmask_prefix));
                get_first_last_host(bin_network, bin_broadcast);
            }

            /*
                OUTPUT END
            */
        }
    }
    if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);
}

void show_interfaces()
{
    struct ifaddrs* ifAddrStruct = NULL;
    struct ifaddrs* ifa = NULL;
    void* tmpAddrPtr = NULL;

    getifaddrs(&ifAddrStruct);

    std::cout << "List of active interfaces" << std::endl;

    for(ifa = ifAddrStruct;  ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr) continue;
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            std::cout << "> " << ifa->ifa_name << std::endl;
        }
    }
    if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);
}