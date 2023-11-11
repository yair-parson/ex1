#include "RLEList.h"
struct RLEList_t{
    //TODO: implement
    char c;
    int count; // equal to 1 if single char
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
    while(list != NULL){
        tmp = list;
        list = tmp -> next;
        free(tmp);
    }
    return;
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if(list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list->next != NULL) // get to the last node in the list
    {
        list = list->next;
    }

    if(list->c == value) // added same char two or more times in a row, need to implement the RLE method of adding it
    {
        list->count += 1; // add another appereance to the char
    }

    else // gotta add a new node
    {
        RLEList new_node = (RLEList)malloc(sizeof(*new_node)); // could use the ListCreate but the documentation says its for new lists
        if(new_node == NULL)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        new_node->c = value;
        new_node->count = 1;
        new_node->next = NULL;
        list->next = new_node;
    }
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if(list == NULL)
    {
        return -1;
    }
    int size = 0;
    while(list!= NULL)
    {
        size += list->count;
    }
    return size;
}

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
    *result = RLE_LIST_SUCCESS;
    return list->c;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(result == NULL)
    {
        return NULL; // cant pass it through the result var cause its null
    }

    if(list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int required_size = find_exported_size(list); // calculates total size needed for the exported string
    char* exported_string = (char*)malloc(required_size +1); // +1 for NULL
    int i=0;
    while(list!=NULL)
    {
        exported_string[i++] = list->c;
        
        sprintf(exported_string, "%d", list->count); // inserting number into string
        i += find_digit_count(list->count); // inserting the number takes up this space so gotta have i catch up with it
        exported_string[i++] = '\n';
    }
    *result = RLE_LIST_SUCCESS;
    return exported_string;
}
int find_exported_size(RLEList list)
{
    int size = 0;
    int temp =0;
    while(list !=NULL)
    {
        size +=2; // for the char and newline
        temp = list->count;
        size += find_digit_amount(temp);
        list = list->next;
    }
    return size;
}
int find_digit_count(int num)
{
    int dig = 0;
    while(num>0)
    {
        dig+=1; // for any number, any digit is a place in the array, for 10 it would be 2 places, for 165 3 and for 3 1 etc..
        num/=10;
    }
    return num;
}
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list!=NULL)
    {
        list->c = map_function(list->c);
        list = list->next;
    }
    return RLE_LIST_SUCCESS;
}



