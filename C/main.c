#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    void quickSort( int first, int last, int x,int longestWordLength, char names[x][longestWordLength]);
    int compare(char base[], char toCompare[], int startIndex);
    char *replace(char toBeReplaced[], char toBeCopied[], int longestWordLength);
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

    printf("%d\n",finalWordCount);

    for (int k = 0; k <= finalWordCount-1; k++) {
        printf("%s\n",names[k]);
    }
    printf("\n");




 quickSort(0, finalWordCount-1, finalWordCount, longestWordLength, names);

    for (int k = 0; k <= finalWordCount-1; k++) {
        printf("%s",names[k]);
    }
    printf("\n");

    return 0;

}

char *replace(char toBeReplaced[], char toBeCopied[], int longestWordLength) {
    char word[longestWordLength];
    int currentIndex = 0;
    while (toBeCopied[currentIndex] != '\0') {
        toBeReplaced[currentIndex] = toBeCopied[currentIndex];
        currentIndex++;
    }

    return word;

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

void quickSort( int first, int last, int x,int longestWordLength, char names[x][longestWordLength]) {
    int i, j, pivot;
    char temp[longestWordLength];
    if (first<last) {
        pivot = first;
        i = first;
        j = last;

        while (i<j) {

            while (compare(names[i], names[pivot], 0) && i<last) {
                i++;
            }
            printf("%d",i);
            while (compare(names[pivot], names[j], 0)) {
                j--;
            }
            printf("%d",j);

            if(i<j) {
                printf("Swapping %s(position %d) with %s(position %d)\n",names[pivot],pivot, names[j],j);
                replace(temp, names[pivot], longestWordLength);
                replace(names[pivot], names[j], longestWordLength);
                replace(names[j], temp, longestWordLength);
                quickSort(first, j - 1, x, longestWordLength, names);
                quickSort(j + 1, last, x, longestWordLength, names);
            }


        }
    }
}
