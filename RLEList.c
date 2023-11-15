//
// Created by mailr on 15/11/2023.
//

#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

#define END_STRING '\0'
#define FIRST_ASCII 0
#define LAST_ASCII 255
#define MAX_SIZE_MULT 3
#define NEW_LINE '\n'

struct RLEList_t{
    char value;
    RLEList next;
    int appearances;
};

//implement the functions here

RLEList RLEListCreate()
{
    RLEList list = (RLEList)malloc(sizeof(*list));
    if(list == NULL)
    {
        return NULL;
    }
    list->next = NULL;
    list->appearances = 0;
    list->value = END_STRING;
    return list;
}

void RLEListDestroy(RLEList list)
{
    if(list == NULL)
    {
        return;
    }

    while(list->next != NULL)
    {
        RLEList temp = list->next;
        free(list);
        list = temp;
    }

    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if(!list || value < FIRST_ASCII || value > LAST_ASCII)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list->next != NULL)
    {
        list = list->next;
    }

    if(list->value)
    {
        if(list->value == value)
        {
            list->appearances++;
            return RLE_LIST_SUCCESS;
        }
    }

    RLEList temp = (RLEList)malloc(sizeof(*temp));
    if(!temp)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    temp->next = NULL;
    temp->value = value;
    temp->appearances = 1;
    list->next = temp;

    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if(list == NULL)
    {
        return -1;
    }

    int size = 0;
    list = list->next;
    while(list)
    {
        size += list->appearances;
        list = list->next;
    }

    return size;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(index >= RLEListSize(list) || index < 0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    int currentIndex = 0;

    while(currentIndex <= index && list->next != NULL)
    {
        if(currentIndex + list->next->appearances - 1 >= index)
        {
            list->next->appearances--;
            if(list->next->appearances == 0)
            {
                list->next = list->next->next;
            }
            return RLE_LIST_SUCCESS;
        }
        else
        {
            currentIndex += list->next->appearances;
            list = list->next;
        }
    }

    return RLE_LIST_ERROR;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(!list)
    {
        if(result)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return '0';
    }

    if(index >= RLEListSize(list) || index < 0)
    {
        if(result)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return '0';
    }

    int currentIndex = 0;

    while(currentIndex <= index && list->next != NULL)
    {
        if(currentIndex + list->next->appearances - 1 >= index)
        {
            if(result)
            {
                *result = RLE_LIST_SUCCESS;
            }

            return list->next->value;
        }
        else
        {
            currentIndex += list->next->appearances;
            list = list->next;
        }
    }

    if(result)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return '0';

}


char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(list == NULL)
    {
        if(result)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }

    int size = RLEListSize(list);

    char* RLEString = (char*)malloc(sizeof(char) * (size * MAX_SIZE_MULT + 1));
    if(!RLEString)
    {
        if(result)
        {
            *result = RLE_LIST_OUT_OF_MEMORY;
            return NULL;
        }
    }

    int curr = 0;
    while(list->next)
    {
        RLEString[curr++] = list->next->value;
        sprintf(RLEString + curr, "%d", list->next->appearances);
        curr = strlen(RLEString);
        RLEString[curr++] = NEW_LINE;
        list = list->next;
    }

    if(result)
    {
        *result = RLE_LIST_SUCCESS;
    }

    RLEString[curr] = END_STRING;
    return RLEString;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(!list || !map_function)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    list = list->next;
    while(list)
    {
        list->value = map_function(list->value);
        list = list->next;
    }
}

