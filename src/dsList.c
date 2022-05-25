#include "dsListFunctions.h"
#include "dsUniversal.h"

struct _list{
    Type type; 
    void (*deleteData)(void *toBeDeleted);
    int (*compare)(const void *first,const void *second);
    void (*printData)(void *toBePrinted);
    char *(*toString)(void *toMakeString);
    int len;
    struct _listNode *head;
    struct _listNode *tail;

};

struct _listNode{
    unsigned int pos;
    void *data;
    struct _listNode *next;
    struct _listNode *prev;
};

List *newList(void (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second),char *(*toString)(void *toMakeString)){

    //int all values
    List *list = NULL;
    list = malloc(sizeof(List));
    allocationError("List *newList(void (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second),char *(*toString)(void *toMakeString))", list);

    list->type = ULIST;
    list->head = NULL;
    list->tail = NULL;
    list->len = -1;
    list->printData = printFunction;
    list->compare = compareFunction;
    list->deleteData = deleteFunction;
    list->toString = toString;

    return list;
}

ListNode *newListNode(void *data, int currLen){
    
    //init all values
    ListNode *listNode = NULL;
    listNode = malloc(sizeof(ListNode));
    allocationError("ListNode *newListNode(void *data, int currLen)",listNode);
    
    listNode->pos = currLen;
    listNode->data = data;
    listNode->next = NULL;
    listNode->prev = NULL;

    return listNode;
}

void listInsertBack(List *list, void *toAdd){

    if(nullArgError("void listInsertBack(List *list, void *toAdd)",list,1)) return;
    if(nullArgError("void listInsertBack(List *list, void *toAdd)",toAdd,2)) return;

    list->len = list->len + 1;

    ListNode *node = newListNode(toAdd,list->len);

    //empty list
    if(list->head == NULL && list->tail == NULL){
        list->head = node;
        list->tail = list->head;
    }else{
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    
}

void listInsertFront(List* list, void* toBeAdded){

    if(nullArgError("void listInsertFront(List* list, void* toBeAdded)",list,1)) return;
    if(nullArgError("void listInsertFront(List* list, void* toBeAdded)",toBeAdded,2)) return;

    list->len = list->len + 1;

    ListNode *node = newListNode(toBeAdded,list->len);

    //empty list
    if(list->head == NULL && list->tail == NULL){
        list->head = node;
        list->tail = list->head;

    }else{
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

void listInsertAfterPosition(List *list, int pos, void *toAdd){

    if(nullArgError("void listInsertAfterPosition(List *list, int pos, void *toAdd)",list,1)) return;
    if(negVArgError("void listInsertAfterPosition(List *list, int pos, void *toAdd)",pos,2)) return;
    if(nullArgError("void listInsertAfterPosition(List *list, int pos, void *toAdd)",toAdd,3)) return;

    if(pos >= list->len){
        listInsertBack(list,toAdd);
        return;
    }

    if(list->head == NULL && list->tail == NULL){
        listInsertBack(list,toAdd);
        return;

    }else{
        ListNode *currNode = list->head;
        
        while(currNode != NULL){
            
            //add after position
            if(currNode->pos == pos){
                list->len = list->len + 1;
                
                ListNode *nodeToAdd = newListNode(toAdd,pos + 1);
                nodeToAdd->next = currNode->next;
                nodeToAdd->prev = currNode;
                
                if(currNode->next == NULL){
                    list->tail = nodeToAdd;
                }

                currNode->next = nodeToAdd;

            }
            currNode = currNode->next;
        }
    }
    updateListPositions(list);
}

void listInsertAfterData(List *list, void *dataPos, void *toAdd){
    
    if(nullArgError("void listInsertAfterData(List *list, void *dataPos, void *toAdd)",list,1)) return;
    if(nullArgError("void listInsertAfterData(List *list, void *dataPos, void *toAdd)",dataPos,2)) return;
    if(nullArgError("void listInsertAfterData(List *list, void *dataPos, void *toAdd)",toAdd,3)) return;
    if(missingFunctionError("void listInsertAfterData(List *list, void *dataPos, void *toAdd)",list->compare)) return;

    ListNode *currNode = list->head;

    while(currNode != NULL){

        //match found
        if(list->compare(dataPos,currNode->data)){
            list->len = list->len + 1;
            ListNode *nodeToAdd = newListNode(toAdd,currNode->pos + 1);
            nodeToAdd->next = currNode->next;
            nodeToAdd->prev = currNode;

            currNode->next = nodeToAdd;

            if(currNode->next == NULL){
                list->tail = nodeToAdd;
            }
        }

        currNode = currNode->next;
    }
    updateListPositions(list);
}

void *listGetFromFront(List *list){

    if(nullArgError("void *listGetFromFront(List *list)",list,1)) return NULL;
    if(nullArgError("void *listGetFromFront(List *list)",list->head,1)) return NULL;

    return list->head->data;
}

void *listGetFromBack(List *list){

    if(nullArgError("void *listGetFromBack(List *list)",list,1)) return NULL;
    if(nullArgError("void *listGetFromBack(List *list)",list->tail,1)) return NULL;

    return list->tail->data;
}

void *listGetAtPosition(List *list, int pos){

    if(nullArgError("void *listGetAtPosition(List *list, int pos)",list,1)) return NULL;
    if(nullArgError("void *listGetAtPosition(List *list, int pos)",list->head,1)) return NULL;
    if(negVArgError("void *listGetAtPosition(List *list, int pos)",pos,2)) return NULL;

    if(pos > list->len){
        return listGetFromBack(list);
    }

    ListNode *currNode = list->head;

    while(currNode != NULL){
        if(currNode->pos == pos){
            return currNode->data;
        }

        currNode = currNode->next;
    }
    return NULL;
}

void freeList(List *list){

    if(nullArgError("void freeList(List *list)",list,1)) return;
    
    void *v = (void*)list;

    if(list->head != NULL){
        freeListContent(list);
        _free(&v);
    }else{
        _free(&v);

    }
}

void freeListContent(List *list){

    if(nullArgError("void freeListContent(List *list)",list,1)) return;

    ListNode *currNode = list->head;

    while(currNode != NULL){
        ListNode *tmp = currNode;
        list->deleteData(currNode->data);
        currNode->data = NULL;
        currNode = currNode->next;
        void *v = tmp;
        _free(&v);
        
    }
    list->len = -1;
}

void *listRemoveAtPosition(List *list, int pos){

    if(nullArgError("void freeListContent(List *list)",list,1)) return NULL;
    if(negVArgError("void listRemoveAtPosition(List *list, int pos)",pos,2)) return NULL;

    ListNode *tmp = list->head;
    void *returnData = NULL;

    while(tmp != NULL){
        
        if(tmp->pos == pos){
            ListNode *bye = tmp;

            //list head
            if(tmp->prev != NULL){
                tmp->prev->next = bye->next;
            }else{
                list->head = bye->next;
            }

            if(tmp->next != NULL){
                tmp->next->prev = bye->prev;
            }else{
                list->tail = bye->prev;
            }

            returnData = bye->data;
            
            void *v = (void *)bye;
            _free(&v);
            
            break;

        }else{
            tmp = tmp->next;
        }
    }

    list->len = list->len - 1;
    updateListPositions(list);

    return returnData;
}

void *listRemoveData(List *list, void *toBeDeleted){
    
    if(nullArgError("void *listRemoveData(List *list, void *toBeDeleted)",list,1)) return NULL;
    if(nullArgError("void *listRemoveData(List *list, void *toBeDeleted)",toBeDeleted,2)) return NULL;
    if(missingFunctionError("void *listRemoveData(List *list, void *toBeDeleted)",list->compare)) return NULL;

    ListNode *tmp = list->head;
    void *returnData = NULL;

    while(tmp != NULL){
        
        if(list->compare(tmp->data, toBeDeleted) == 0){

            ListNode *bye = tmp;

            if(tmp->prev != NULL){
                tmp->prev->next = bye->next;
            }else{
                list->head = bye->next;
            }

            if(tmp->next != NULL){
                tmp->next->prev = bye->prev;
            }else{
                list->tail = bye->prev;
            }

            returnData = bye->data;

            void *v = (void *)bye;
            _free(&v);
            
            break;

        }else{
            tmp = tmp->next;
        }

    }

    list->len = list->len - 1;
    updateListPositions(list);

    return returnData;
}

List *listJoin(List **dest, List **src){

    if(nullArgError("void listJoin(List *dest, List *src)",*dest,1)) return NULL;
    if(nullArgError("void listJoin(List *dest, List *src)",(*dest)->head,1)) return NULL;
    if(nullArgError("void listJoin(List *dest, List *src)",src,2)) return NULL;
    if(nullArgError("void listJoin(List *dest, List *src)",(*src)->head,2)) return NULL;

    List *list = newList((*dest)->printData,(*dest)->deleteData,(*dest)->compare,(*dest)->toString);

    ListNode *curr = (*dest)->head;

    list->len = (*dest)->len + (*src)->len;

    //add first
    while(curr != NULL){
        ListNode *tmp = curr;
        listInsertBack(list,curr->data);
        curr = curr->next;
        void *v = (void *)tmp;
        _free(&v);
        
    }
    
    list->tail = (*src)->tail;

    //add second
    curr = (*src)->head;
    while(curr != NULL){
        ListNode *tmp = curr;
        listInsertBack(list,curr->data);
        curr = curr->next;
        void *v = (void *)tmp;
        _free(&v);
    }
    
    void *v = (void *)src;
    _free(v);
    v = (void *)dest;
    _free(v);

    
    updateListPositions(list);
    return list;
}   

void updateListPositions(List *list){

    ListNode *currNode = list->head;

    for(int i = 0; i < list->len; i++){
        currNode->pos = i;
        currNode = currNode->next;
    }
}

int listlength(List *list){
    return (list == NULL) ? 0 : list->len + 1;
}

int listIsEmpty(List *list){
    return (list == NULL || list->head == NULL || list->tail == NULL) ? 1: 0;
}

void listPrint(List *list){

    if(nullArgError("void listPrint(List *list)",list,1)) return;
    if(missingFunctionError("void listPrint(List *list)",list->printData)) return;

    ListNode *node = list->head;

    while(node != NULL){
        list->printData(node->data);
        node = node->next;
    }
}

char *listToString(List *list){
    
    if(nullArgError("char *listToString(List *list)",list,1)) return NULL;
    if(nullArgError("char *listToString(List *list)",list->head,1)) return NULL;
    if(missingFunctionError("char *listToString(List *list)",list->toString)) return NULL;

    char *retStr = malloc(sizeof(char)*2);
    allocationError("char *listToString(List *list)",retStr);
    strcpy(retStr,"");
    ListNode *currNode = list->head;

    while(currNode != NULL){
        char *str = list->toString(currNode->data);
        int sz = strlen(retStr);
        retStr = realloc(retStr,sizeof(char)*(sz + strlen(str) + 1));
        allocationError("char *listToString(List *list)",retStr);
        strcat(retStr,str);
        void *v = (void *)str;
        _free(&v);

        currNode = currNode->next;
    }
    strcat(retStr,"\0");
    return retStr;
}