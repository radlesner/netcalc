#include <stdio.h>
#include <stdlib.h>

void mainOutput(unsigned int *ipAddrTab, unsigned int rawMaskPrefix);
void additionalInterfaceOutput(char *interfaceName);
_Noreturn void helpOutput(void);
_Noreturn void invalidArgumentsOutput(int argc, char *argv[]);
