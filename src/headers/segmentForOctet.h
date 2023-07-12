#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OCTETS 4
#define MAX_OCTET_SIZE 4

void getOctet(unsigned int ipAddrTab[], const char *ipAddr);
void getMask(unsigned int ipNetMaskTab[], unsigned int maskPrefix);