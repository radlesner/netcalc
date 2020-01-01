#include "headers/octet.h"

std::string division_on_octet(std::string ip4_addr, int which_octet)
{
    std::string
        ip_octet[4],
        netmask_octet[4];

    int octet_indicator = 0;

    for (std::string::iterator i = ip4_addr.begin(); i != ip4_addr.end(); i++)
    {
        if (*i == '.')
        {
            octet_indicator++;
            i++;
        }

        ip_octet[octet_indicator] += *i;
    }

    return ip_octet[which_octet];
}