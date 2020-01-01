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
#include "output.h"
#include "check_ip.h"
#include "check_prefix.h"

void get_network_argument(char *ip_argument, char *prefix_argument);
void get_network_inteface(char *interface_name);
void show_interfaces();
