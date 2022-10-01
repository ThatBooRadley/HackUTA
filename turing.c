#include <stdio.h>
#define MEM_LEN 3000

int index = 0;
char memory[MEM_LEN];

void right(int num)
{
    index += num;
}

void left(int num)
{
    index += num;
}

char read()
{
    return memory[index];
}

void write(char num)
{
    memory[index] = num;
}
