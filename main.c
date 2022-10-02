#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct map
{
    char* key;
    char** value;
} dict;

struct map* translate(char* in, struct map* dict);
void convert(char* in, struct map* dict, int length);

int main(int argc, char** argv)
{
    FILE* din = fopen(argv[1], "r");    //dictionary first
    int defSize = 0;

    fscanf(din, "%d", &defSize);
    fclose(din);

    struct map* dictionary = calloc(defSize, sizeof(struct map));
    dictionary = translate(argv[1], dictionary);
    convert(argv[2], dictionary, defSize);
    return 0;
}

struct map* translate(char* in, struct map* dict) //converts map input file into map array structure
{
    FILE* din = fopen(in, "r");
    int index = 0;
    while(!feof(din))
    {
        char buffer[256];
        fscanf(din, "%s", buffer);
        if(strcmp(buffer, "<<") == 0)
        {
            char buff[256];
            fscanf(din, "%s", buff);
            (dict[index]).key = malloc(strlen(buff));
            memcpy((dict[index]).key, buff, strlen(buff)+1);
        }
        else if(strcmp(buffer, "::") == 0)
        {
            (dict[index]).value = malloc(sizeof((dict[index]).value));
            int i=1;
            (dict[index]).value[i] = malloc(4);
            fscanf(din, "%s", buffer);
            while(strcmp(buffer, ">>") != 0)
            {
                (dict[index]).value[i] = malloc(strlen(buffer)+1);
                memcpy((dict[index]).value[i], buffer, strlen(buffer)+1);
                i++;
                fscanf(din, "%s", buffer);
            }
            itoa(i, (dict[index]).value[0], 10);
            index++;
        }
    }
    printf("%s\n", (dict[0]).value[2]);
    for(int i=0; i< 2;i++)
    {
        printf("<<%s ::", dict[i].key);
        for(int j=0;j< atoi(dict[i].value[0]);j++)
        {
            printf("%s ", (dict[i]).value[j]);
        }
        printf(">>\n");
    }
    return dict;
}

void convert(char* in, struct map* dict, int length)
{
    FILE* fin = fopen(in, "r");
    FILE* fout = fopen("fout.c", "w");
    int index = 0;
    while(!feof(fin))
    {
        char buffer[8];
        fscanf(fin, "%s", buffer);
        for(int i=0; i<length; i++)
        {
            if(strcmp(buffer, (dict[i]).key) == 0)
            {
                for(int j=1; j < atoi((dict[i]).value[0]);j++)
                {
                    fprintf(fout, "%s", (dict[i]).value[j]);
                }
                break;
            }
        }
    }
    fclose(fout);
}