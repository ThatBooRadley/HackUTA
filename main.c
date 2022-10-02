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

struct map* translate(char* in, struct map* dict)
{
    FILE* din = fopen(in, "r");
    int index = 0;
    while(!feof(din))
    {
        char buffer[256];
        fscanf(din, "%s", buffer);
        if(strcmp(buffer, "<<") == 0)
        {
            printf("<<\n");
            char buff[256];
            fscanf(din, "%s", buff);
            (dict[index]).key = malloc(strlen(buff));
            memcpy((dict[index]).key, buff, strlen(buff)+1);
            printf("%s , %s, %d, %d\n", (dict[index]).key, buff, strlen((dict[index]).key), strlen(buff));
        }
        else if(strcmp(buffer, "::") == 0)
        {
            printf("::\n");
            int i=1;
            (dict[index]).value = malloc(sizeof((dict[index]).value));
            do
            {
                fscanf(din, "%s", buffer);
                (dict[index]).value[i] = malloc(strlen(buffer)+1);
                memcpy((dict[index]).value[i], buffer, strlen(buffer)+1);
                i++;
            }while(strcmp(buffer, ">>") != 0);
            sprintf((dict[index]).value[0], "%d", i);
            for(int j=1;j<i;j++)
            {
                printf("%s\n", (dict[index]).value[j]);
            }
            printf(">>\n");
        }
    }
    printf("%d", index);
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