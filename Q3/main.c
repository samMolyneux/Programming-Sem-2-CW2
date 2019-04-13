#include <stdio.h>
#include <stdlib.h>

#define WORDS 10
#define LETTERS 3
int hash(char key[], int keyLength, int tableSize);
int isFree( int currentIndex, char hashArray[WORDS][LETTERS]);
void insert(char word[], char hashArray[WORDS][LETTERS]);


int main() {


    char hashArray[WORDS][LETTERS] = {0};
    for(int i = 0; i <=WORDS-1; i++){
        for(int f = 0; f <= LETTERS -1; f++){
            hashArray[i][f] = 0;
        }
    }


    insert("AB", hashArray);
    insert("CC", hashArray);
    insert("ZA", hashArray);

    for(int i = 0; i <=WORDS-1; i++){
        for(int f = 0; f <= LETTERS -1; f++){
            printf("%c", hashArray[i][f]);
        }
        printf("\n");
    }
    return 0;
}

void insert(char word[], char hashArray[WORDS][LETTERS]){

    int startIndex = hash(word, LETTERS, WORDS);
    int index = startIndex;
    while(!isFree(index, hashArray)){
        index++;
        if(index==WORDS-1){
            index=0;
        }
        if(index == startIndex){
            printf("table full");
            break;
        }
    }
    for(int i = 0; i <= LETTERS-1; i++){
        hashArray[index][i] = word[i];
    }


}

int hash(char key[], int keyLength, int tableSize){
    int hashVal = 1;

    for (int i = 0; i < keyLength; i++){
        hashVal = hashVal*31 + key[i];
    }
    printf("%s", hashVal);
    return hashVal % tableSize;
}

int isFree( int currentIndex, char hashArray[WORDS][LETTERS]){
    char *firstChar = hashArray[LETTERS*currentIndex];

    if (*firstChar != NULL){
        return 0;
    } else{
        return 1;
    }

}