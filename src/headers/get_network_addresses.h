#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sstream>
#include <netpacket/packet.h>

#include "octet.h"
#include "convert_numbers.h"
#include "ip_operations.h"
#include "netmask.h"

void get_network(char *interface_name);
void show_interfaces();
