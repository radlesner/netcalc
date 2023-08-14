#include "headers/strings.h"

void segmentLines(char *table_output[], const char *str_input)
{
    int newlineCount = 0;
    int lenght       = strlen(str_input);
    int y            = 0;
    int x            = 0;
    char buffer[64]  = "";

    for (int i = 0; i < lenght; i++)
    {
        if (str_input[i] == '\n')
        {
            sprintf(table_output[x], buffer);
            printf("%s\n", table_output[x]);

            newlineCount++;
            y = 0;
            x++;

            memset(buffer, 0, sizeof(buffer));
        }
        else
        {
            // strcat(table_output, str_input[i]);
            // printf("%c\n", str_input[i]);

            buffer[y] = str_input[i];
            // table_output[newlineCount][y] = str_input[i];
            y++;
        }
    }

    // printf("%s\n", table_output[0]);
}