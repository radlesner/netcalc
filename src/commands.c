#include "headers/commands.h"

int isCommandAvailable(const char* command)
{
    char checkCmd[512];
    int boolResult;

    snprintf(checkCmd, sizeof(checkCmd), "which %s >/dev/null 2>&1", command);

    FILE* fp = popen(checkCmd, "r");
    if (fp == NULL)
    {
        perror("Błąd polecenia 'popen'");
        boolResult = 0; // FALSE
    }
    else
        boolResult = 1; // TRUE

    pclose(fp);
    return boolResult;
}

void getCommandResult(char resultOutput[], char* command)
{
    char buffer[256];

    FILE* fp = popen(command, "r");
    if (fp == NULL)
    {
        perror("popen");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        strcpy(resultOutput, buffer);
    }

    pclose(fp);
}
