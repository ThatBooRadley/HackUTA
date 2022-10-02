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

int main(int argc, char* argv[])
{
    char * argv2 = malloc(strlen(argv[2])+1);
    memcpy(argv2, argv[2], strlen(argv[2])+1);
    FILE* din = fopen(argv[1], "r");    //dictionary first
    int defSize = 0;
    fscanf(din, "%d", &defSize);
    fclose(din);
    struct map* dictionary = calloc(defSize, sizeof(struct map));
    dictionary = translate(argv[1], dictionary);
    convert(argv2, dictionary, defSize);

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
            (dict[index]).key = malloc(strlen(buff)+1);
            memcpy((dict[index]).key, buff, strlen(buff)+1);
        }
        else if(strcmp(buffer, "::") == 0)
        {
            (dict[index]).value = malloc(sizeof((dict[index]).value));
            int i=1;
            fscanf(din, "%s", buffer);
            (dict[index]).value[0] = malloc(sizeof(buffer));
            (dict[index]).value[i] = malloc(sizeof(buffer));
            while(strcmp(buffer, ">>") != 0)
            {
                (dict[index]).value[i] = malloc(strlen(buffer)+1);
                memcpy((dict[index]).value[i], buffer, strlen(buffer)+1);
                i++;
                fscanf(din, "%s", buffer);
            }
            if(index == 1)
                printf("%s\n", (dict[1]).value[0]);
            sprintf((dict[index]).value[0], "%d",i);
            if(index == 1)
                printf("%s\n", (dict[1]).value[0]);
            index++;
        }
    }
    
        //TESTING TRANSLATE
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
    char buffer[256];
    while(index < length)
    {
        fscanf(fin, "%s", buffer);
        for(int j=0;j<sizeof(dict[0])/sizeof(dict);j++) //each word in dict
        {
            if(memcmp(buffer, (dict[j]).key, strlen(buffer)) == 0)
            {
                for(int c=1; c < atoi((dict[j]).value[0]);c++)  //each word in value
                {
                    printf("%s ", (dict[j]).value[c]);
                    fprintf(fout, "%s ", (dict[j]).value[c]);
                }
                break;
            }
        }
        index++;
    }
    fclose(fout);
}