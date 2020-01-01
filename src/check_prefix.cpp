#include "headers/check_prefix.h"

bool is_valid_netmask_prefix(std::string netmask_prefix)
{
    if (netmask_prefix.length() == 1)
    {
        if (static_cast<int>(netmask_prefix[0]) >= 48 && static_cast<int>(netmask_prefix[0]) <= 57)
        {
            if (std::stoi(netmask_prefix) < 0 || std::stoi(netmask_prefix) > 31)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    if (netmask_prefix.length() == 2)
    {
        if (static_cast<int>(netmask_prefix[1]) >= 48 && static_cast<int>(netmask_prefix[1]) <= 57)
        {
            if (std::stoi(netmask_prefix) < 0 || std::stoi(netmask_prefix) > 31)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}