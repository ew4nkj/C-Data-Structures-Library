#include "dsGeneric.h"

typedef struct _dsGen{
    Type type;
}Generic;

int isEmpty(void *dataStructure){
    
    if(nullArgError("int isEmpty(void *dataStructure)",dataStructure,1)) return 1;
    
    Generic *ds = (Generic *)dataStructure;

    switch(ds->type){
        case ULIST:
            return listIsEmpty((List *)dataStructure);
            break;
        case USTACK:
            return stackIsEmpty((Stack *)dataStructure);
            break;
        case UQUEUE:
            return queueIsEmpty((Queue *)dataStructure);
            break;
        case UHASHTABLE:
            return hashTableIsEmpty((HashTable *)dataStructure);
            break;
        default:
            break;
    }

    return 1; 
}

void toPrint(void *dataStructure){

    if(nullArgError("void toPrint(void *dataStructure)",dataStructure,1)) return;

    Generic *ds = (Generic *)dataStructure;

    switch(ds->type){
        case ULIST:
            listPrint((List *)dataStructure);
            break;
        case USTACK:
            stackPrint((Stack *)dataStructure);
            break;
        case UQUEUE:
            queuePrint((Queue *)dataStructure);
            break;
        case UHASHTABLE:
            hashTablePrint((HashTable *)dataStructure);
            break;
        default:
            break;
    }   
}

char *toString(void *dataStructure){
    
    if(nullArgError("char *toString(void *dataStructure)",dataStructure,1)) return NULL;

    Generic *ds = (Generic *)dataStructure;

    switch(ds->type){
        case ULIST:
            return listToString((List *)dataStructure);
            break;
        case USTACK:
            return stackToString((Stack *)dataStructure);
            break;
        case UQUEUE:
            return queueToString((Queue *)dataStructure);
            break;
        case UHASHTABLE:
            return hashTableToString((HashTable *)dataStructure);
            break;
        default:
            break;
    }

    return NULL; 
}