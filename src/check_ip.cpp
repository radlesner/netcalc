#include "headers/check_ip.h"

bool is_valid_ip(const std::string& ipStr)
{
    int ip3, ip2, ip1, ip0;
    if (4 != sscanf(ipStr.c_str(), "%d.%d.%d.%d", &ip3, &ip2, &ip1, &ip0))
    {
        return false;
    }
    for (auto p : {&ip3, &ip2, &ip1, &ip0})
    {
        if ((*p > 255) || (*p < 0))
        {
            return false;
        }
    }
    return true;
}