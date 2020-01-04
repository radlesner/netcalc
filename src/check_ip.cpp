#include "headers/check_ip.h"

bool valid_digit(char *ip_str)
{
    while (*ip_str) {
        if (*ip_str >= '0' && *ip_str <= '9')
            ++ip_str;
        else
            return false;
    }
    return true;
}

bool is_valid_ip(char *ip_str)
{
    int num,
        dots = 0;

    char *ptr;

    if (ip_str == NULL)
        return false;

    // See following link for strtok()
    // http://pubs.opengroup.org/onlinepubs/009695399/functions/strtok_r.html
    ptr = strtok(ip_str, DELIM);

    if (ptr == NULL)
        return false;

    while (ptr) {

        /* after parsing string, it must contain only digits */
        if (!valid_digit(ptr))
            return false;

        num = std::stoi(ptr);

        /* check for valid IP */
        if (num >= 0 && num <= 255) {
            /* parse remaining string */
            ptr = strtok(NULL, DELIM);
            if (ptr != NULL)
                ++dots;
        } else
            return false;
    }

    /* valid IP string must contain 3 dots */
    if (dots != 3)
        return false;
    return true;
}