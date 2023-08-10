#include <arpa/inet.h>
#include <errno.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <systemd/sd-bus.h>
#include <unistd.h>

int maskToPrefix(unsigned int maskAddr[]);
void getInterfaceInfo(char *interfaceName, unsigned int ipAddr[], unsigned int ipMask[]);
void showInterfaces(void);
bool isExistInterface(char *interfaceName);
void getMacAddress(char *macAddress, char *interfaceName);
void getGatewayAddr(unsigned int ipGatewayAddr[], char *interfaceName);
int isDhcpConfig(const char *interface);
void getDnsAddress(unsigned int ipDnsAddrTab[], char *interfaceName);
