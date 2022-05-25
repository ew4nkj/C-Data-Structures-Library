#include "dsHashtableFunctions.h"

struct _hashTable{
    Type type;
    void (*deleteData)(void *toBeDeleted);
    int (*compare)(const void *first,const void *second);
    void (*printData)(void *toBePrinted);
    char *(*toString)(void *toMakeString);
    unsigned int totalElements;
    unsigned int tableSize;
    struct _hashNode *content;

};

struct _hashNode{
    unsigned int pos;
    char *key;
    void *data;
};

unsigned int hash(char *key, unsigned int tableSize){

    unsigned long keyLen = strlen(key);

    unsigned int hashCode = 0;

    for(int i = 0; i < keyLen; i++){
        hashCode = (SMALL_PRIME * hashCode + (unsigned int)key[i]) % tableSize;
    }

    return hashCode;
}

HashTable *newHashTable(void (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second),char *(*toString)(void *toMakeString)){

    HashTable *table = malloc(sizeof(HashTable));
    allocationError("HashTable *newHashTable(void (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second),char *(*toString)(void *toMakeString))",table);

    table->totalElements = 0;
    table->tableSize = DEFAULT_HASH_SIZE;
    table->type = UHASHTABLE;
    
    HashNode *tblContent = malloc(sizeof(HashNode)*DEFAULT_HASH_SIZE);
    allocationError("HashTable *newHashTable(void (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second),char *(*toString)(void *toMakeString))",tblContent);

    for(int i = 0; i < DEFAULT_HASH_SIZE; i++){
        tblContent[i].data = NULL;
        tblContent[i].key = NULL;
        tblContent[i].pos = INT_MAX;
    }

    table->content = tblContent;

    table->compare = compareFunction;
    table->printData = printFunction;
    table->deleteData = deleteFunction;
    table->toString = toString;

    return table;
}

void hashTableInsert(HashTable *table, char *key, void *toAdd){

    if(nullArgError("void hashTableInsert(HashTable *table, char *key, void *toAdd)",table,1)) return;
    if(nullArgError("void hashTableInsert(HashTable *table, char *key, void *toAdd)",key,2)) return;
    if(nullArgError("void hashTableInsert(HashTable *table, char *key, void *toAdd)",toAdd,3)) return;

    if(table->totalElements == table->tableSize - 1){
        return;
    }


    unsigned int hashCode = hash(key,table->tableSize);

    for(int i = 0; i < table->tableSize; i++){

       unsigned int index = (i + hashCode) % table->tableSize;

       if(table->content[index].pos == INT_MAX){
           
           table->content[index].key = malloc(sizeof(char)*strlen(key)+1);
           allocationError("void hashTableInsert(HashTable *table, char *key, void *toAdd)",table->content[index].key);
           
           strcpy(table->content[index].key,key);
           strcat(table->content[index].key,"\0");

           table->content[index].data = toAdd;
           table->content[index].pos = index;

           table->totalElements = table->totalElements + 1;

           return;
       }
   }
}

void *hashTableSearch(HashTable *table, char *key){

    if(nullArgError("void *hashTableSearch(HashTable *table, char *key)",table,1)) return NULL;
    if(nullArgError("void *hashTableSearch(HashTable *table, char *key)",key,2)) return NULL;

    unsigned int hashCode = hash(key,table->tableSize);

    for(int i = 0; i < table->tableSize; i++){

        unsigned int index = (i + hashCode) % table->tableSize;
        
        if(table->content[index].key != NULL){

            if(table->content[index].pos != INT_MAX && strcmp(table->content[index].key,key) == 0){
                return table->content[index].data;
            }
        }
    }

    return NULL;
}

void *hashTableRemove(HashTable *table, char *key){

    if(nullArgError("void hashTableRemove(HashTable *table, char *key)",table,1)) return NULL;
    if(nullArgError("void hashTableRemove(HashTable *table, char *key)",key,2)) return NULL;

    unsigned int hashCode = hash(key, table->tableSize);
    void *returnData = NULL;

    for(int i = 0; i < table->tableSize; i++){

        unsigned int index = (i + hashCode) % table->tableSize;

        if(table->content[index].key != NULL){

            if(table->content[index].pos != INT_MAX && strcmp(table->content[index].key,key) == 0){

                table->content[index].pos = INT_MAX;
                
                void *v = (void *)table->content[index].key;
                _free(&v);

                returnData = table->content[index].data;
                table->content[index].data = NULL;
                
                table->totalElements = table->totalElements - 1;
                break;
            }
        }

    }

    return returnData;
    
}

void feeHashTableContent(HashTable *table){

    if(nullArgError("void feeHashTableContent(HashTable *table)",table,1)) return;
    if(missingFunctionError("void feeHashTableContent(HashTable *table)",table->deleteData)) return;

    for(int i = 0; i < table->tableSize; i++){

        if(table->content[i].pos != INT_MAX){
            
            void *v = (void*)table->content[i].key;
            _free(&v);

            table->content[i].pos = INT_MAX;
            
            table->deleteData(table->content[i].data);
            table->content[i].data = NULL;
        }
    }
    
    table->totalElements = 0;
}

void freeHashTable(HashTable *table){
    
    if(nullArgError("void freeHashTable(HashTable *table)",table,1)) return;

    feeHashTableContent(table);

    void *v = (void *)table->content;
    _free(&v);

    v = (void *)table;
    _free(&v);
}

void hashTablePrint(HashTable *table){

    if(nullArgError("void hashTablePrint(HashTable *table)",table,1)) return;
    if(missingFunctionError("void hashTablePrint(HashTable *table)",table->printData)) return;

    for(int i = 0; i < table->tableSize; i++){

        if(table->content[i].pos != INT_MAX){
            table->printData(table->content[i].data);
        }
    }
}

int hashTableUsage(HashTable *table){
    return (table == NULL) ? 0 : table->totalElements;
}

int hashTableSize(HashTable *table){
    return (table == NULL) ? 0 : table->tableSize;
}

char *hashTableToString(HashTable *table){

    if(nullArgError("char *hashTableToString(HashTable *table)",table,1)) return NULL;
    if(missingFunctionError("char *hashTableToString(HashTable *table)",table->toString)) return NULL;

    char *retStr = malloc(sizeof(char)*2);
    allocationError("char *retStr = malloc(sizeof(char)*2)",retStr);
    strcpy(retStr,"");

    for(int i = 0; i < table->tableSize; i++){

        if(table->content[i].pos != INT_MAX){
            
            char *str = table->toString(table->content[i].data);
            
            int sz = strlen(retStr);
            
            retStr = realloc(retStr,sizeof(char)*(sz + strlen(str) + 1));
            allocationError("char *retStr = malloc(sizeof(char)*2)",retStr);
            strcat(retStr,str);
            
            void *v = (void *)str;
            _free(&v);
        }
    }
    
    return retStr;
}

void hashTableSetBound(HashTable *table, unsigned int bound){
    
    if(nullArgError("void hashTableSetBound(HashTable *table, unsigned int bound)",table,1)) return;

    if(table->totalElements != 0){
        if(hashChangeBoundError("void hashTableSetBound(HashTable *table, unsigned int bound)",table->tableSize,bound)) return;
    }

    void *v = (void *)table->content;
    _free(&v);

    table->tableSize = bound;

    HashNode *newNodes = malloc(sizeof(HashNode)*bound);

    for(int i = 0; i < bound; i++){
        
        newNodes[i].pos = INT_MAX;
        newNodes[i].key = NULL;
        newNodes->data = NULL;
    }

    table->content = newNodes;
}

int hashTableIsEmpty(HashTable *table){
    return (table == NULL || table->totalElements == 0) ? 1 : 0;
}
