#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__) || defined(__ghostbsd__)

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BSD_SYSTEM
#else

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
#include <unistd.h>

#define OTHER_SYSTEM
#endif

int maskToPrefix(unsigned int maskAddr[]);
void getInterfaceInfo(char *interfaceName, unsigned int ipAddr[], unsigned int ipMask[]);
void showInterfaces(void);
bool isExistInterface(char *interfaceName);
void getMacAddress(char *macAddress, char *interfaceName);
void getGatewayAddr(unsigned int ipGatewayAddr[], char *interfaceName);
int isStaticInterface(const char *interface);
