#include <stdio.h>
#include <stdlib.h>

int getLength(char *word);
int main(int argc, char* argv[]) {

    char input[5000];
    char *plaintext = argv[1];


    FILE *filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("no file found");
    }else {
        char nextChar = fgetc((FILE *) filePointer);
        int count = 0;
        while (nextChar != EOF) {
            input[count] = nextChar;
            nextChar = fgetc((FILE *) filePointer);
            count++;
        }
        input[count] = '\0';

        plaintext = input;
    }
    char *key = argv[2];

    int wordLength = getLength(plaintext);
    int keyLength = getLength(key);

    int columnLength = wordLength/keyLength;
    if(wordLength%keyLength != 0){
        columnLength++;
    }

    char table[keyLength][columnLength];

    int currentPosition = 0;

    printf("\n");
    for(int i = 0; i <= wordLength-1; i++){
        printf("%c", plaintext[i]);
    }
    printf("\n");

    for(int i = 0; i <= keyLength-1; i++){
        currentPosition = i;
        for(int j = 0; j <= columnLength -1; j++) {
            if (currentPosition <= wordLength - 1) {
                table[i][j] = plaintext[currentPosition];
            }
            else{
            table[i][j] = 'X';

        }
                //printf("%c", plaintext[currentPosition]);
                currentPosition = currentPosition + keyLength;
        }
    }


    printf("%d\n\n", columnLength);

    int n = keyLength;
    for(int i=0; i < n; i++){
        //checks each item against all non-sorted items
        for(int j=1; j < (n-i); j++) {
            if(key[j-1]<key[j]){
                char temp = key[j-1];
                key[j-1] = key[j];
                key[j] = temp;

                char tempArray[keyLength];

                for(int k = 0; k <= columnLength-1; k++){
                    tempArray[k] = table[j-1][k];
                }
                for(int k = 0; k <= columnLength-1; k++){
                    table[j-1][k] = table[j][k];
                }
                for(int k = 0; k <= columnLength-1; k++){
                    table[j][k] = tempArray[k];
                }
            }
        }
        }

    for(int i =0; i <= keyLength-1; i++){
        for(int j = 0; j <= columnLength -1; j++){
            printf("%c", table[i][j]);
        }
    }
    return 0;
}

int getLength(char *word){
    int length = 0;
    while(word[length] !='\0'){
        length++;
    }
    printf("\n%d", length);
    return length;
}