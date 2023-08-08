#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IP4_MAX_OCTET 4

void getWildAddr(unsigned int ipWildTab[], unsigned int ipMaskTab[]);
void getNetworkAddr(unsigned int ipNetAddrTab[], unsigned int ipAddrTab[], unsigned int ipMaskTab[]);
void getBroadAddr(unsigned int ipBroadAddrTab[], unsigned int ipNetAddrTab[], unsigned int ipMaskTab[]);
void getFirstLastHost(unsigned int ipFirstHost[], unsigned int ipLastHost[], unsigned int ipNetAddrTab[], unsigned int ipBroadAddrTab[]);
unsigned int getHostNumber(unsigned int rawMaskPrefix);
int ipcmp(unsigned int ipTab[], int oct1, int oct2, int oct3, int oct4);
