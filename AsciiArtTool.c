//
// Created by mailr on 15/11/2023.
//

#include "AsciiArtTool.h"
#include <stdlib.h>

RLEList asciiArtRead(FILE *in_stream)
{

    fseek(in_stream, 0, SEEK_END);
    int length = ftell(in_stream);

    fseek(in_stream, 0, SEEK_SET);

    char* string = (char*)malloc(sizeof(char)*(length + 1));

    RLEList list = RLEListCreate();
    char c;
    while((c = (char)fgetc(in_stream)) != EOF)
    {
        RLEListAppend(list, c);
    }

    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE* out_stream)
{
    if(list == NULL || out_stream == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int index = 0;
    int length = RLEListSize(list);
    while(index < length)
    {
        fputc(RLEListGet(list,index,NULL), out_stream);
        index++;
    }

    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream)
{
    if(list == NULL || out_stream == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    char* string = RLEListExportToString(list, NULL);
    int index = 0;

    while(string[index])
    {
        fputc(string[index], out_stream);
        index++;
    }

    return RLE_LIST_SUCCESS;
}