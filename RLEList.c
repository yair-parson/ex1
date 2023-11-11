#include "RLEList.h"

struct RLEList_t{
    //TODO: implement
    char c;
    int appear;
    RLEList* next;
};//typedef declares in the header file

//implement the functions here

RLEList RLEListCreate();

void RLEListDestroy(RLEList list);

RLEListResult RLEListAppend(RLEList list, char value);

int RLEListSize(RLEList list);

RLEListResult RLEListRemove(RLEList list, int index);

char RLEListGet(RLEList list, int index, RLEListResult *result);

char* RLEListExportToString(RLEList list, RLEListResult* result);

RLEListResult RLEListMap(RLEList list, MapFunction map_function);



