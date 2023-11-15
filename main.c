#include <stdio.h>
#include "RLEList.h"


char addOneToAscii(char c)
{
    if((int)c == 255)
    {
        return (char)1;
    }
    return (char)((int)c + 1);
}


int main()
{

    RLEListResult r1;
    RLEListResult* result = &r1;
    RLEList list = RLEListCreate();
    RLEListAppend(list, 'A');
    RLEListAppend(list, 'A');
    RLEListAppend(list, 'B');
    RLEListAppend(list, 'B');


    RLEListMap(list, addOneToAscii);
    printf("CHAR: %c\n", RLEListGet(list, 7, result));
    char* RLEString = RLEListExportToString(list, result);
    if(*result == RLE_LIST_SUCCESS)
    {
        printf("%s", RLEString);
    }

    return 0;
}
