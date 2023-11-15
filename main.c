#include <stdio.h>
#include "RLEList.h"
#include "AsciiArtTool.h"
#include <string.h>

char mapFunction(char c)
{
    if(c == '@')
    {
        return ' ';
    }

    else if(c == ' ')
    {
        return '@';
    }

    return c;
}


int main(int argc, char** argv)
{

    if(argc != 4)
    {
        printf("Usage: ./AsciiArtTool.c (i/e) (sourceFile) (targetFile)");
        return 1;
    }
    FILE* inFile = fopen(argv[2], "r"); // source file
    FILE* outFile = fopen(argv[3], "w"); // target file


    RLEList list = asciiArtRead(inFile);


    if(strcmp(argv[1],"-i") == 0)
    {
        RLEListMap(list, mapFunction);
        asciiArtPrint(list, outFile);
        fclose(inFile);
        fclose(outFile);
        return 0;
    }

    else if (strcmp(argv[1],"-e") == 0)
    {
        asciiArtPrintEncoded(list, outFile);
        fclose(inFile);
        fclose(outFile);
        return 0;
    }

    else
    {
        printf("Usage: ./main.c (i/e) (sourceFile) (targetFile)");
        fclose(inFile);
        fclose(outFile);
        return 1;
    }
}
