#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    void quickSort(int left, int right,int words, int letters, char names[words][letters]);
    int compare(char base[], char toCompare[], int startIndex);
    char *replace(char toBeReplaced[], char toBeCopied[], int longestWordLength);
    int partitionMaker(int left, int right, int pivot, int words, int letters, char names[words][letters]);
    /*for(int i = 2; i <= argc; i++){
        int j = 0;
        while(argv[i][j] != '/0'){
            input[i-2][j] = argv[i][j];
        }
        input[i-2][j+1] = '/0';
    }*/
    char input[8192][64];



    FILE *filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("no file found");
        exit(EXIT_FAILURE);
    }
    int wordCounter = 0;
    int longestWordTracker = 0;
    int letterCounter = 0;
    int nextChar = fgetc((FILE *) filePointer);
    char currentName[64];


    while (nextChar != EOF) {
        if (nextChar == '"') {
        } else if (nextChar == ',') {
            for (int j = 0; j <= letterCounter; j++) {
                input[wordCounter][j] = currentName[j];
                input[wordCounter][j + 1] = '\0';
                //currentName[j] = 0;
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
        //currentName[j] = 0;
    }
    input[wordCounter][letterCounter] = '\0';
    if (letterCounter > longestWordTracker) {
        longestWordTracker = letterCounter + 1;
    }
    wordCounter++;

    fclose((FILE *) filePointer);

    int finalWordCount = wordCounter;
    int longestWordLength = longestWordTracker;


    char names[finalWordCount][longestWordLength];

    for (int i = 0; i <=finalWordCount-1; i++) {
        for (int pr = 0; pr <= longestWordLength; pr++) {
            names[i][pr] = 0;
        }
    }

    for (int a = 0; a <= finalWordCount - 1; a++) {
        for (int b = 0; b <= longestWordLength - 1; b++) {
                names[a][b] = input[a][b];

            }

        }

    for (int k = 0; k <= finalWordCount-1; k++) {
        for (int j = 0; j <= longestWordLength - 1; j++) {
            printf("%c", names[k][j]);
        }
        printf("end");
        printf("\n");
    }

    quickSort(0, finalWordCount-1, finalWordCount, longestWordLength, names);
    for (int k = 0; k <= finalWordCount-1; k++) {
        for (int j = 0; j <= longestWordLength - 1; j++) {
            printf("%c", names[k][j]);
        }
        printf("end");
        printf("\n");
    }

    return 0;

}


int partitionMaker(int left, int right, int pivot, int words, int letters, char names[words][letters]){
    int compare(char base[], char toCompare[], int startIndex);
    int leftPointer = left;
    int rightPointer = right -1;

    while(1){
        while(compare(names[pivot],names[leftPointer],0)){
            leftPointer++;
        }
        while(rightPointer>0 && compare(names[pivot],names[rightPointer],0)){
            rightPointer--;
        }
        if(leftPointer>=rightPointer){
            break;
        } else{
            for(int j = 0; j <= letters-1; j++){
                char temp = names[leftPointer][j];
                names[leftPointer][j] = names[rightPointer][j];
                names[rightPointer][j] = temp;
            }
        }
    }
    for(int j = 0; j <= letters-1; j++){
        char temp = names[leftPointer][j];
        names[leftPointer][j] = names[right][j];
        names[right][j] = temp;
    }
    return leftPointer;
}

void quickSort(int left, int right, int words, int letters, char names[words][letters]){
    int pivot;
    int partition;
    if (right-left <= 0){
        return;
    }
    else{
        pivot = right;
        partition = partitionMaker(left, right, pivot, words, letters, names);

        quickSort(left, partition-1, words, letters, names);
        quickSort(partition+1, right, words, letters, names);
    }

}


//true if toCompare should be before base
int compare(char base[], char toCompare[], int startIndex) {
    if (base[startIndex] == '\0') {
        return 0;
    } else if (toCompare[startIndex] == '\0') {
        return 1;
    }

    if (base[startIndex] > toCompare[startIndex]) {
        return 1;
    } else if (base[startIndex] == toCompare[startIndex]) {
        return compare(base, toCompare, startIndex + 1);
    } else {
        return 0;
    }
}

