#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER 1024

#define START_CMD    0
#define STOP_CMD     1
#define RESTART_CMD  2
#define STATUS_CMD   3
#define EXIT_CMD     4
#define UNKNOWN_CMD  -1
int main(int argc, char* argv[])
{
    char *cmds[] = {"start", "stop", "restart", "status", "exit"};
    char cmd[BUFFER];
    while (fputs("> ", stdout) != EOF && scanf("%s", cmd) == 1)
    {
        int i = 0;
        int index = UNKNOWN_CMD;
        for (; index == UNKNOWN_CMD && i < (int)(sizeof(cmds)/sizeof(cmds[0])); ++i)
        { 
            index = strcmp(cmd, cmds[i]) == 0 ? i : UNKNOWN_CMD;
        } 
        switch (index)
        {
            case START_CMD:
            {
                printf("command %s recognized\n", cmds[START_CMD]);
                break;
            }
            case STOP_CMD:
            {
                printf("command %s recognized\n", cmds[STOP_CMD]);
                break;
            }
            case RESTART_CMD:
            {
                printf("command %s recognized\n", cmds[RESTART_CMD]);
                break;
            }
            case STATUS_CMD:
            {
                printf("command %s recognized\n", cmds[STATUS_CMD]);
                break;
            }
            case EXIT_CMD: return 0;
            default:
            {
                fputs("Invalid command\n", stdout);
            }
        }
    }
    
    return 0;
}