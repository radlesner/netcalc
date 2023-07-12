#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getWildAddr(unsigned int ipWildTab[], unsigned int ipMaskTab[]);
void getNetworkAddr(unsigned int ipNetAddrTab[], unsigned int ipAddrTab[], unsigned int ipMaskTab[]);
void getBroadAddr(unsigned int ipBroadAddrTab[], unsigned int ipNetAddrTab[], unsigned int ipMaskTab[]);
void getFirstLastHost(unsigned int ipFirstHost[], unsigned int ipLastHost[], unsigned int ipNetAddrTab[], unsigned int ipBroadAddrTab[]);
unsigned int getHostNumber(unsigned int rawMaskPrefix);
