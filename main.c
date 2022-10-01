#include <stdio.h>

struct map
{
    char* key;
    char* value;
};

int main(int argc, char** argv)
{
    FILE* fin = fopen(argv[1], "r");
    int defSize = 0;
    fscanf(fin, "%d", &defSize);
    struct map* dictionary = calloc(defSize, sizeof(struct map));

    //translate(fin);
    return 0;
}

FILE* translate(FILE* fin)
{
    return 0;
}