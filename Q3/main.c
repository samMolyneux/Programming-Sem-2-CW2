#include <stdio.h>


#define WORDS 20000
#define LETTERS 64
int hash(char key[], int keyLength, int tableSize);
int isFree( int currentIndex, char hashArray[WORDS][LETTERS]);
void add(char word[], char hashArray[WORDS][LETTERS]);
int search(char name[], char hashArray[WORDS][LETTERS]);
void delete(char name[], char hashArray[WORDS][LETTERS]);


int collisions = 0;

char nameHolder[LETTERS];
int main(int argc, char* argv[]) {

    char input[8192][64];



    FILE *filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("no file found");
    }
    int wordCounter = 0;
    int longestWordTracker = 0;
    int letterCounter = 0;
    int nextChar = fgetc((FILE *) filePointer);
    char currentName[64];


    while (nextChar != EOF) {
        if (nextChar == '"') {
        } else if (nextChar == ',') {
            for (int j = 0; j <= letterCounter-1; j++) {
                input[wordCounter][j] = currentName[j];
                input[wordCounter][j + 1] = '\0';
            }
            if (letterCounter > longestWordTracker) {
                longestWordTracker = letterCounter + 1;
            }
            letterCounter = 0;
            wordCounter++;

        } else {
            currentName[letterCounter] = nextChar;
            letterCounter++;
        }

        nextChar = fgetc((FILE *) filePointer);
    }

    for (int j = 0; j <= letterCounter; j++) {
        input[wordCounter][j] = currentName[j];
    }
    input[wordCounter][letterCounter] = '\0';
    if (letterCounter > longestWordTracker) {
        longestWordTracker = letterCounter + 1;
    }
    wordCounter++;

    fclose((FILE *) filePointer);

    char hashArray[WORDS][LETTERS] = {};




    for(int j = 0; j <= wordCounter-1; j++){
        //printf("Inserting: %s\n", input[j]);
        add(input[j], hashArray);
    }
/*
    for(int i = 0; i <=WORDS-1; i++){
        for(int f = 0; f <= LETTERS -1; f++){
            printf("%c", hashArray[i][f]);
        }
        printf("\n");
    }
*/

    printf("Collisions: %d", collisions);

    delete("MARY", hashArray);
    return 0;
}

void add(char word[], char hashArray[WORDS][LETTERS]){

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
        //printf("char: %c",word[i]);
        hashArray[index][i] = word[i];
    }
    //exit(2);
}

int hash(char key[], int keyLength, int tableSize){
    int hashVal = 1;

    for (int i = 0; i < keyLength; i++){
        hashVal = hashVal*31 + key[i];
    }
    if(hashVal<0){
        hashVal = hashVal *-1;
    }

    return hashVal % tableSize;
}

void setNameHolder(char name[]){
    int i = 0;
    while(name[i] != '\0'){
        nameHolder[i] = name[i];
        i++;
    }
    nameHolder[i] = '\0';
    for(int j = i; j <= LETTERS-1; j++) {
        nameHolder[i] = 0;
    }

}
void delete(char name[], char hashArray[WORDS][LETTERS]){

    setNameHolder(name);
    int hashIndex = hash(nameHolder, LETTERS, WORDS);

    if(search(nameHolder, hashArray)) {
        int i = 0;
        while (1) {
        while (hashArray[hashIndex][i] == nameHolder[i]) {
            if (nameHolder[i] == '\0') {
                for (int j = 0; j <= LETTERS - 1; j++) {
                    hashArray[hashIndex][j] = 0;
                }
                return;
            }
            i++;
        }
        hashIndex++;
    }


    }else{
        printf("%s is not in array", name);
    }


}
int search(char name[], char hashArray[WORDS][LETTERS]) {
    setNameHolder(name);
    int hashIndex = hash(nameHolder, LETTERS, WORDS);
    int i = 0;
    while (hashArray[hashIndex][0] != 0) {
        if (hashArray[hashIndex][i] != nameHolder[i]) {
            hashIndex++;
        } else if (nameHolder[i] == '\0') {
            return 1;
        } else {
            i++;
        }
    }
    return 0;
}


int isFree( int currentIndex, char hashArray[WORDS][LETTERS]){
    //printf("%d", currentIndex);

    char firstChar = hashArray[currentIndex][0];

    if (firstChar != 0){
        collisions++;

        return 0;
    } else{

        return 1;
    }

}