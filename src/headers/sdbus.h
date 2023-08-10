#include <arpa/inet.h>
#include <systemd/sd-bus.h>
#include <unistd.h>

int isSDBUSavailable(void);
void getSDBUS_dns_IP_address(char SDBUSoutput[]);
