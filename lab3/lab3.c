#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utf8.h"

#define STR_LEN 1024
#define ARR_SIZE 300  // enough size
#define BUF_SIZE 20480

// definition of language blocks
typedef struct Block
{
    unsigned int head;  // begining
    unsigned int tail;  // end
    char name[STR_LEN];  // block name
}Block;

Block blocks[ARR_SIZE];
int count[ARR_SIZE] = {0};  // count the languages

void read_blocks(const char* file_name);  // read block files
int search(int codepoint);  // search block which the character belongs to
char* major_block(void);  // find the most appeared language

int main(int argc, char const *argv[])
{
    read_blocks("Blocks.txt");
    char buffer[BUF_SIZE];
    while(fgets(buffer, BUF_SIZE, stdin))  // read from stdin
    {
        unsigned char *ptr;
        ptr = (unsigned char *)buffer;
        int lenptr = 0;
        while (*ptr != '\0')  // loop until reach the end of the line
        {
            search(utf8_to_codepoint(ptr, &lenptr));
            ptr += lenptr;
        }
        memset(buffer, '\0', BUF_SIZE);  // reset array
    }
    fprintf(stdout, "%s\n", major_block());
    return 0;
}

void read_blocks(const char* file_name)
{
    FILE *file = fopen(file_name, "r");
    if(file == NULL)
    {   // if file is not found...
        fputs("Error: No such file!\n", stderr);
    }
    else
    {
        char line[STR_LEN];
        int index;
        int num = 0;
        for (index = 0; !feof(file) && !ferror(file) && fgets(line, STR_LEN, file); ++index, \
                memset(line, 0, STR_LEN))
        {
            if (line[0] == '#' || line[0] == ' ' || line[0] == '\n')
            {
                continue;
            }
            Block new_block;
            char* rest = NULL;
            char* token = NULL;
            token = strtok_r(line, ".; ", &rest);  // get head
            sscanf(token, "%x", &new_block.head);
            token = strtok_r(rest, ".; ", &rest);  // get tail
            sscanf(token, "%x", &new_block.tail);
            rest[strlen(rest)-1] = '\0';
            ++rest;
            strcpy(new_block.name, rest);  // get block name
            blocks[num++] = new_block;  // store blocks
        }
    }
    fclose(file);  // close file
}

int search(int codepoint)
{
    int i, index = -1;
    for(i = 0; i < ARR_SIZE; ++i)
    {
        if(codepoint >= blocks[i].head && codepoint <= blocks[i].tail)
        {   // if codepoint is within the range of certain language block, increase the counter
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
    {   // find index of the most appeared language
        if(count[i] > num)
        {
            num = count[i];
            index_of_majority = i;
        }
    }
    if (index_of_majority != -1)
    {
        return blocks[index_of_majority].name;  //return the name
    }
    return "";
}