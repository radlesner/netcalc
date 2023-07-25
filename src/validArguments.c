#include "headers/validArguments.h"

bool isIPValid(const char *ipAddress)
{
    int ip3, ip2, ip1, ip0;
    if (4 != sscanf(ipAddress, "%d.%d.%d.%d", &ip3, &ip2, &ip1, &ip0))
    {
        return false;
    }
    int *ipArray[] = {&ip3, &ip2, &ip1, &ip0};
    for (int i = 0; i < 4; i++)
    {
        int *p = ipArray[i];
        if ((*p > 255) || (*p < 0))
        {
            return false;
        }
    }
    return true;
}

bool isMaskValid(const char *maskPrefixStr)
{
    int i = 0;
    int intPrefix;

    if (maskPrefixStr[i] == '-') i++;

    while (maskPrefixStr[i] != '\0')
    {
        if (!isdigit(maskPrefixStr[i])) return false;
        i++;
    }

    intPrefix = atoi(maskPrefixStr);

    if (intPrefix < 0 || intPrefix > 31)
    {
        return false;
    }

    return true;
}
