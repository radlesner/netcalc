#include "headers/get_network_addresses.h"
#include "headers/check_ip.h"
#include "headers/check_prefix.h"
#include "headers/convert_numbers.h"
#include "headers/ip_operations.h"
#include "headers/netmask.h"
#include "headers/octet.h"
#include "headers/output_messages.h"

void get_network_argument(const std::string &ip_argument, const std::string &prefix_argument)
{
    std::string binary_ip_address, binary_netmask, binary_wildcard, binary_network, binary_broadcast;
    int prefix_netmask;

    if (!is_valid_netmask_prefix(prefix_argument))
    {
        error_message();
        usage_message();
        return;
    }
    else
        prefix_netmask = std::stoi(prefix_argument);

    if (!is_valid_ip(ip_argument))
    {
        error_message();
        usage_message();
        return;
    }

    std::cout << "IP address:        " << ip_argument << " (" << add_valid_color("OK") << ")" << std::endl;
    binary_ip_address = make_bin_address(ip_argument);
    binary_netmask = make_netmask(prefix_netmask);
    binary_wildcard = make_wildcard_mask(prefix_netmask);
    binary_network = get_network_address(binary_ip_address, binary_netmask);
    binary_broadcast = get_broadcast_addr(binary_network, binary_wildcard);
    get_first_last_host(binary_network, binary_broadcast);
    get_number_hosts(binary_ip_address, prefix_netmask);
}

void get_network_inteface(const std::string &interface_name)
{
    struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;
    const void *tmpAddrPtr = nullptr;
    int netmask_prefix;
    std::string bin_ip_address, bin_netmask, bin_wildcard, bin_network, bin_broadcast;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
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

            if (static_cast<std::string>(ifa->ifa_name) == interface_name)
            {
                std::cout << "Interface:         " << ifa->ifa_name << "\n"
                          << "IP address:        " << address_buffer << "\n"
                          << "Netmask:           " << mask_buffer << "\n";

                bin_ip_address = make_bin_address(address_buffer);
                bin_netmask = make_bin_address(mask_buffer);
                netmask_prefix = make_prefix(bin_netmask);
                bin_wildcard = make_wildcard_mask(netmask_prefix);
                bin_network = get_network_address(bin_ip_address, bin_netmask);
                bin_broadcast = get_broadcast_addr(bin_network, bin_wildcard);
                get_first_last_host(bin_network, bin_broadcast);
                get_number_hosts(bin_ip_address, netmask_prefix);
            }
        }
    }
    if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);
}

void show_interfaces()
{
    struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;

    getifaddrs(&ifAddrStruct);
    std::cout << "List of active interfaces" << std::endl;

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr) continue;
        if (ifa->ifa_addr->sa_family == AF_INET) std::cout << "> " << ifa->ifa_name << std::endl;
    }
    if (ifAddrStruct != NULL) freeifaddrs(ifAddrStruct);
}

std::string add_valid_color(std::string text_input) { return "\033[1;32m" + text_input + "\033[0m"; }