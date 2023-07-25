#include "headers/ipOperations.h"

void getWildAddr(unsigned int ipWildTab[], unsigned int ipMaskTab[])
{
    for (int i = 0; i < 4; i++)
    {
        ipWildTab[i] = ipMaskTab[i] ^ 255;
    }
}

void getNetworkAddr(unsigned int ipNetAddrTab[], unsigned int ipAddrTab[], unsigned int ipMaskTab[])
{
    for (int i = 0; i < 4; i++)
    {
        ipNetAddrTab[i] = ipAddrTab[i] & ipMaskTab[i];
    }
}

void getBroadAddr(unsigned int ipBroadAddrTab[], unsigned int ipNetAddrTab[], unsigned int ipMaskTab[])
{
    for (int i = 0; i < 4; i++)
    {
        ipBroadAddrTab[i] = ipNetAddrTab[i] | (~ipMaskTab[i] & 0xFF);
    }
}

void getFirstLastHost(unsigned int ipFirstHost[], unsigned int ipLastHost[], unsigned int ipNetAddrTab[], unsigned int ipBroadAddrTab[])
{
    for (int i = 0; i < 4; i++)
    {
        ipFirstHost[i] += ipNetAddrTab[i];
        ipLastHost[i] += ipBroadAddrTab[i];

        if (i == 3)
        {
            ipFirstHost[i] += 1;
            ipLastHost[i] -= 1;
        }
    }
}

unsigned int getHostNumber(unsigned int rawMaskPrefix)
{
    unsigned int numHost;

    numHost = (1 << (32 - rawMaskPrefix)) - 2;
    return numHost;
}
