
#include "dsErrorHandling.h"

void allocationError(char *functionName, void *data){
    
    if(!data){
        #ifdef DEBUG
            fprintf(stderr,"FATAL ERROR: %s failed due to a failure with memory allocation. This could be due to malloc(), realloc(), or calloc() returning NULL.\n",functionName);
        #endif
        exit(EXIT_FAILURE);
    }
}

bool nullArgError(char *functionName, void *data, int narg){

    if(data == NULL){
        #ifdef DEBUG
            fprintf(stderr,"ERROR: %s cannot except a null argument for argument %d.\n",functionName,narg);
        #endif
        return true;
    }
    return false;
}

bool negVArgError(char *functionName, int value, int narg){
    
    if(value < 0){
        #ifdef DEBUG
            fprintf(stderr,"ERROR: %s cannot accept %d as it is bellow 0.\n",functionName,value);
        #endif
        return true;
    }
    return false;
}

bool missingFunctionError(char *functionName, void *func){

    if(!func){
        #ifdef DEBUG
            fprintf(stderr,"ERROR: %s is missing a requried function within the structure itself thus, the called function is unavailable.\n",functionName);
        #endif
        return true;
    }
    return false;
}

bool hashChangeBoundError(char *functionName, unsigned int rBound, unsigned int tBound){

    #ifdef DEBUG
        fprintf(stderr,"ERROR: %s hash table was initilized with %d and has inserted data. the hash table cannot have it's size changed to %d\n",functionName,rBound,tBound);
    #endif 
    return true;    
}
