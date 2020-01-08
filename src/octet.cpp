#include "headers/octet.h"

std::vector<std::string> get_octet(std::string ip4_addr)
{
    std::vector<std::string> ip_octet;
    std::string octet_buffer[4];
    int octet_indicator = 0;

    for (std::string::iterator i = ip4_addr.begin(); i != ip4_addr.end(); i++)
    {
        if (*i == '.')
        {
            octet_indicator++;
            i++;
        }

        octet_buffer[octet_indicator] += *i;
    }

    for (size_t i = 0; i < 4; i++)
    {
        ip_octet.push_back(octet_buffer[i]);
    }

    return ip_octet;
}

std::vector<std::string> get_bin_octets(std::string bin_addr)
{
    std::vector<std::string> bin_octet;
    std::string octet_buffer[4];
    int octet_indicator = 0;

    for (size_t i = 0; i < bin_addr.length(); i++)
    {
        octet_buffer[octet_indicator] += bin_addr[i];

        if (i == 7 || i == 15 || i == 23)
        {
            octet_indicator++;
        }
    }

    for (size_t i = 0; i < 4; i++)
    {
        bin_octet.push_back(octet_buffer[i]);
    }

    return bin_octet;
}