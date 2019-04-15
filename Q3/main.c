#include <stdio.h>


#define WORDS 20000
#define LETTERS 64
int hash(char key[], int keyLength, int tableSize);
int isFree( int currentIndex, char hashArray[WORDS][LETTERS]);
void add(char word[], char hashArray[WORDS][LETTERS]);
int search(char name[], char hashArray[WORDS][LETTERS]);
void delete(char name[], char hashArray[WORDS][LETTERS]);

//used to track the efficiency of the sorting algorithm
int collisions = 0;

//used as a temporary holder
char nameHolder[LETTERS];

//takes the file
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

    //searches through the file, creating arrays of characters and adding them to the main array
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

    //adding the final word as file doesnt end with ','
    for (int j = 0; j <= letterCounter-1; j++) {
        input[wordCounter][j] = currentName[j];
        //printf("%c",currentName[j]);
    }
    wordCounter++;
    input[wordCounter][letterCounter] = '\0';

    fclose((FILE *) filePointer);

    char hashArray[WORDS][LETTERS] = {};

    //adds all the words to the hash
    for(int j = 0; j <= wordCounter-1; j++){
        //printf("Inserting: %s\n", input[j]);
        add(input[j], hashArray);
    }
    char *inName;
    char inChar;
    int i;


        printf("Hash table created with %d collisions\n", collisions);

        printf("Type 1 to delete a word\n");
        printf("Type 2 to search for a word\n");
        printf("Type 3 to add a word\n");
        printf("Type 4 to output to file\n");
        printf("Type 5 to exit\n");


        inChar = scanf(filePointer, "%s", inName, &i);

        switch (inChar) {
            case '1':
                printf("Type the word you wish to delete");
                inName = fgets(inName, LETTERS, filePointer);
                delete(inName, hashArray);
                break;
            case '2':
                printf("Type the word you wish to search for");
                inName = fgets(inName, LETTERS, filePointer);
                search(inName, hashArray);
                break;
            case '3':
                printf("Type the word you wish to add");
                inName = fgets(inName, LETTERS, filePointer);
                add(inName, hashArray);
                break;
            case '4':
                for (int i = 0; i <= WORDS - 1; i++) {
                    int k = 0;
                    while (hashArray[i][k] != NULL) {
                        printf(hashArray[i][k]);
                    }
                }
                break;
            default:
                break;

        }
        if(inChar == 5){
        }



    return 0;
}

/**
 * add a word to the hash table
 * @param word the word to add to the hash table
 * @param hashArray the hash table
 */
void add(char word[], char hashArray[WORDS][LETTERS]){
    //the first index tried is the hash of the word
    int startIndex = hash(word, LETTERS, WORDS);
    int index = startIndex;

    //continue to check if the location is free
    //once one is found, enter the word
    //if the table is full, report it
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

/**
 * returns the hash value of the array
 * @param key the word to be added
 * @param keyLength the length of the word
 * @param tableSize the size of the table
 * @return the hashed value
 */
int hash(char key[], int keyLength, int tableSize){
    int hashVal = 1;

    //hash the value be summing each letter multiplied by a prime
    for (int i = 0; i < keyLength; i++){
        hashVal = hashVal*31 + key[i];
    }
    //ensures its positive
    if(hashVal<0){
        hashVal = hashVal *-1;
    }

    //gets the modulus to ensure it is within the table size
    return hashVal % tableSize;
}

/**
 * sets the name holder to a given name to ensure the array is of the correct
 * * @param name to add to the holder
 */
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

/**
 * removes a word from the array and replaces it with null
 * @param name
 * @param hashArray
 */
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
/**
 * checks the array to see if an item is in the hash table
 * @param name the name to be searched for
 * @param hashArray the hash table
 * @return 1 if the name is in the area, 0 if not
 */
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

/**
 * Checks whether the given location is occupied and keeps track of the position
 * @param currentIndex location to be checked
 * @param hashArray the hash table
 * @return true(1) is its free false(0) if not
 */

int isFree( int currentIndex, char hashArray[WORDS][LETTERS]){
    char firstChar = hashArray[currentIndex][0];

    if (firstChar != 0){
        collisions++;

        return 0;
    } else{

        return 1;
    }

}