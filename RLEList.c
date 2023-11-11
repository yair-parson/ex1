#include "RLEList.h"
struct RLEList_t{
    //TODO: implement
    char c;
    int count;
    RLEList next;
};//typedef declares in the header file

//implement the functions here

RLEList RLEListCreate()
{
    RLEList head = malloc(sizeof(*RLEList));
    if (head == NULL){
        return NULL;
    }
    return head;
}

void RLEListDestroy(RLEList list)
{
    RLEList tmp;
    while(list != Null){
        tmp = list;
        list = tmp -> next;
        free(tmp)
    }
    return;
}

RLEListResult RLEListAppend(RLEList list, char value);

int RLEListSize(RLEList list);

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index> RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList previus;
    while (index >0)
    {
        index -= list->count;
        previus = list;
        list = list -> next;//forwards the pointer to the wanted node at the end of the loop
    }
    list->count += -1;
    if(list->count==0)
    {
        previus->next = list->next;
        free(list);
        return RLE_LIST_SUCCESS;
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(list==NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if(index> RLEListSize(list))
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    while(index>0)
    {
        index -= list->count;
        list = list->next;
    }
    *result = LIST_SUCCESS;
    return list->c;
}

char* RLEListExportToString(RLEList list, RLEListResult* result);

RLEListResult RLEListMap(RLEList list, MapFunction map_function);



