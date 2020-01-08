#include "headers/check_ip.h"

bool valid_digit(char *ip_str)
{
    while (*ip_str)
    {
        if (*ip_str >= '0' && *ip_str <= '9')
            ++ip_str;
        else
            return false;
    }
    return true;
}

bool is_valid_ip(char *ip_str)
{
    int   num, dots = 0;
    char *ptr;

    if (ip_str == NULL)
        return false;
    ptr = strtok(ip_str, DELIM);

    if (ptr == NULL)
        return false;

    while (ptr)
    {
        if (!valid_digit(ptr))
            return false;

        num = std::stoi(ptr);

        if (num >= 0 && num <= 255)
        {
            ptr = strtok(NULL, DELIM);
            if (ptr != NULL)
                ++dots;
        }
        else
            return false;
    }

    if (dots != 3)
        return false;
    return true;
}