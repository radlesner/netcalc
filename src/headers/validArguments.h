#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isIPValid(const char *ipAddress);
bool isMaskValid(const char *maskPrefixStr);
