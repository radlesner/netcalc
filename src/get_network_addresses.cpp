#include "headers/get_network_addresses.h"

void get_network_argument(char *ip_argument, char *prefix_argument)
{
    int prefix_netmask = std::stoi(prefix_argument);

    std::string
        ip_address = ip_argument,
        binary_ip_address,
        binary_netmask,
        binary_network,
        binary_broadcast;

    if (!is_valid_netmask_prefix(prefix_netmask))
    {
        error_message();
        usage_message();
        return;
    }

    if (!is_valid_ip(ip_argument))
    {
        error_message();
        usage_message();
        return;
    }

    std::cout
        << "IP address:        " << ip_address
        << " (" << add_color_string("OK") << ")" << std::endl;

    binary_ip_address = make_bin_address(ip_address);
    binary_netmask = make_netmask(prefix_netmask);
    binary_network = get_network_address(binary_ip_address, binary_netmask);
    binary_broadcast = get_broadcast_addr(binary_network, binary_netmask);
    get_number_hosts(binary_ip_address, prefix_netmask);
    get_first_last_host(binary_network, binary_broadcast);
}

void get_network_inteface(char *interface_name)
{
    struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;
    void *tmpAddrPtr = NULL;

    int netmask_prefix;

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
                bin_ip_address = make_bin_address(address_buffer);
                bin_netmask = make_bin_address(mask_buffer);
                netmask_prefix = make_prefix(bin_netmask);

                std::cout
                    << "Interface:         " << ifa->ifa_name << std::endl
                    << "IP address:        " << address_buffer << std::endl
                    << "Netmask:           " << mask_buffer << std::endl;

                bin_network = get_network_address(bin_ip_address, bin_netmask);
                bin_broadcast = get_broadcast_addr(bin_network, bin_netmask);
                get_number_hosts(bin_ip_address, netmask_prefix);
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

std::string add_color_string(std::string text_input)
{
    return "\033[1;32m" + text_input + "\033[0m";
}