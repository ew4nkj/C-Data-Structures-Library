#include "dsUniversal.h"

void _free(void **pptr){
    if(pptr && *pptr){
        free(*pptr);
        *pptr = NULL;
        pptr = NULL;
    }
}