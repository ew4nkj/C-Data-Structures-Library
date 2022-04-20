#include "dsListFunctions.h"
#include <string.h>

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

    //create a new list
    List *letterList = newList(letterToPrint,letterToDelete,letterToCompare,NULL);

    //fill list with ascii
    for(int i = 97; i < 123; i++){
        Letter *l = malloc(sizeof(Letter));
        l->ascii = i;
        l->colour = (char)i;

        listInsertBack(letterList,(void *)l);
    }

    char c[3];
    while(1){

        //get user input
        printf("Favourite letter : ");
        scanf("%s",c);

        if(c[0] < 97 || c[0] > 123){
            break;
        }

        //go through list to see if a match can be made
        for(int i = 0; i <= listlength(letterList); i++){
            
            Letter *testLetter = (Letter *)listGetAtPosition(letterList,i);

            if(testLetter != NULL){
                if(testLetter->colour == c[0]){
                    //print out list content and remove it
                    letterToPrint(testLetter);
                    listRemoveData(letterList,testLetter);
                } 
            }
        }

    }
    //print out remaining list content
    printf("letters you did not like\n");
    listPrint(letterList);

    //free remaining content
    freeList(letterList);
    return EXIT_SUCCESS;
}