#include "headers/commands.h"

int isCommandAvailable(const char *command)
{
    char checkCmd[512];
    int boolResult;

    sprintf(checkCmd, "%s", command);

    FILE *fp = popen(command, "r");
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

void getCommandResult(char resultOutput[], char *inputCommand)
{
    FILE *cmd_output;
    char buffer[256];

    cmd_output = popen(inputCommand, "r");
    if (cmd_output == NULL)
    {
        perror("popen");
        return;
    }

    while (fgets(buffer, sizeof(buffer), cmd_output) != NULL)
    {
        strcat(resultOutput, buffer);
    }

    pclose(cmd_output);
}
