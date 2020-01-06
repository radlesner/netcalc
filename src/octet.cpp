#include "headers/octet.h"

std::vector<std::string> division_on_octet(std::string ip4_addr)
{
    std::vector<std::string>
        ip_octet;

    std::string
        octet_buffer[4];

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