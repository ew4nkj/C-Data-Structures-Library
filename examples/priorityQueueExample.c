#include "dsQueueFunctions.h"

typedef struct _letter{
    int ascii;
    char colour;
}Letter;

void letterToPrint(void *toBePrinted){

    Letter *o = (Letter *)toBePrinted;
    printf("|%c|%d\n",o->colour,o->ascii);
}

int letterToCompare(const void *first,const void *second){

    Letter *o1 = (Letter *)first;
    Letter *o2 = (Letter *)second;

    if(o1->ascii == o2->ascii){
        return 0;
    }
    if(o1->ascii > o2->ascii){
        return 1;
    }
    if(o1->ascii < o2->ascii){
        return -1;
    }

    return 0;
}

void letterToDelete(void *toBeDeleted){

    Letter *o = (Letter *)toBeDeleted;
    free(o);

}

int main(int argc, char *argv[]){
    
    Queue *q = newQueue(PRIORITY,letterToPrint,letterToDelete,letterToCompare,NULL);

    for(int i = 97; i < 123; i++){
        Letter *l = malloc(sizeof(Letter));
        l->ascii = i;
        l->colour = (char)i;

        queuePush(q,l,i);
    }
    
    

    printf("English alphabet\n");
    printf("|c|ascii\n");
    while(!queueIsEmpty(q)){
        Letter *curr = queuePeek(q);
        letterToPrint(curr);
        queuePop(q);
        
    }
    freeQueue(q);
    return EXIT_SUCCESS;
}