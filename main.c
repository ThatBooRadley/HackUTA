#include <stdio.h>
#include <string.h>

struct map
{
    char* key;
    char** value;
};

FILE* translate(FILE* din, struct map* dict);
void convert(FILE* fin, struct map* dict);

int main(int argc, char** argv)
{
    FILE* din = fopen(argv[1], "r");
    int defSize = 0;
    fscanf(din, "%d", &defSize);
    struct map* dictionary = calloc(defSize, sizeof(struct map));

    dictionary = translate(din, dictionary);

    return 0;
}

struct map* translate(FILE* din, struct map* dict)
{
    int index = 0;
    while(!feof(din))
    {
        char* buffer;
        fscanf(din, "%s", &buffer);
        if(strcmp(buffer, "<<"))
        {
            fscanf(din, "%s", &dict[index].key);
        }
        else if(strcmp(buffer, "::"))
        {
            fscanf(din, "%s", buffer);
            for(int i=0;!strcmp(buffer, ">>");i++)
            {
                dict[index].value[i] = buffer;
                fscanf(din, "%s", buffer);
            }
        }
    }    
    return dict;
}

void convert(FILE* fin, struct map* dict)
{
    int index = 0;
    while(!feof(fin))
    {
        char* buffer;
        fscanf(fin, "%s", &buffer);

    }
}