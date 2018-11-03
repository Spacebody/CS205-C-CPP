#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utf8.h"

#define STR_LEN 1024
#define ARR_SIZE 300
#define BUF_SIZE 20480

typedef struct Block
{
    unsigned int head;
    unsigned int tail;
    char name[STR_LEN];
}Block;


Block blocks[ARR_SIZE]; 
int count[ARR_SIZE] = {0};

void read_blocks(const char* file_name);
int search(int codepoint);
char* major_block(void);

int main(int argc, char const *argv[])
{
    read_blocks("Blocks.txt");
    char buffer[BUF_SIZE];
    fgets(buffer, BUF_SIZE, stdin);
    unsigned char *ptr;
    ptr = (unsigned char *)buffer;
    int lengptr = 0;
    do
    {
        search(utf8_to_codepoint(ptr, &lengptr));
        ptr += lengptr;
    } while (*(ptr-1) == '\0');
    fprintf(stdout, "%s\n", major_block());
    return 0;
}

void read_blocks(const char* file_name)
{
    FILE *file = fopen(file_name, "r");
    if(file == NULL)
    {
        fputs("Error: No such file!\n", stderr);
    }
    else
    {
        char line[STR_LEN];
        int index;
        int num = 0;
        for (index = 0; !feof(file) && !ferror(file) && fgets(line, STR_LEN, file); ++index, \
                memset(line, 0, sizeof(STR_LEN)))
        {
            if (line[0] == '#' || line[0] == ' ' || line[0] == '\n')
            {
                continue;
            }
            Block new_block;
            char* rest = NULL;
            char* token = NULL;
            token = strtok_r(line, ".; ", &rest);
            sscanf(token, "%x", &new_block.head);
            token = strtok_r(rest, ".; ", &rest);
            sscanf(token, "%x", &new_block.tail);
            rest[strlen(rest)-1] = '\0';
            ++rest;
            strcpy(new_block.name, rest);
            blocks[num++] = new_block;
        }
    }
    fclose(file);
    // fputs("Read complete!\n", stdout);
}

int search(int codepoint)
{
    int i, index = -1;
    for(i = 0; i < ARR_SIZE; ++i)
    {
        if(codepoint >= blocks[i].head && codepoint <= blocks[i].tail)
        {
            index = i;
            ++(count[index]);
            break;
        }
    }
    return index;
}

char* major_block(void)
{
    int index_of_majority = -1;
    int num = 0;
    int i;   
    for(i = 0; i < ARR_SIZE; ++i)
    {
        if(count[i] > num)
        {
            num = count[i];
            index_of_majority = i;
        }
    }
    if (index_of_majority != -1)
    {
        return blocks[index_of_majority].name;
    }
    return "";
}