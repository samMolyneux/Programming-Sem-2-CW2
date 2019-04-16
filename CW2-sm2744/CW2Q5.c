#include <stdio.h>

#define maxWordsRedacted 100
#define maxRedactedLength 20
int main(int argc, char *argv[]) {

    /**
     * Gets the information from the text file and placed it in the text array
     */
    FILE *filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("no file found");
    }
    char nextChar = fgetc((FILE *) filePointer);
    char text[8192] = {};
    int counter = 0;
    while(nextChar != EOF){
        text[counter] = nextChar;
        counter++;
        nextChar = fgetc((FILE *) filePointer);
    }
    fclose(filePointer);


    /**
     * This block gets the redacted words, keeping track of the number of words and the length of the longest word
     */
    int redacted = 0;
    int maxRedacted = 0;

    char toRedact[maxWordsRedacted][maxRedactedLength];

    filePointer = fopen(argv[2], "r");
    int x = 0;
    int y = 0;
    nextChar = fgetc((FILE *) filePointer);
    int currentCount = 0;
    while(nextChar!= EOF){
        while(nextChar!='\n'){
            currentCount++;
            toRedact[x][y] = nextChar;
            y++;
            nextChar = fgetc((FILE *) filePointer);
        }
        toRedact[x][y] = '\0';
        redacted++;
        y = 0;
        if(currentCount > maxRedacted){
            maxRedacted = currentCount;
        }
        currentCount = 0;
        nextChar = fgetc((FILE *) filePointer);
        x++;
    }
    redacted++;

    fclose(filePointer);

    /**
     * the code that actually changes the text
     */
    char toCheck[maxRedacted];
    printf("\n");

    //loops each individual character
    for(int i = 0; i <= counter-1; i++){
        *toCheck = text[i];
        //makes arrays of characters up to the length of the longest redacted word
        //then checks if it should be redacted
        for(int j = 0; j <= maxRedacted-1; j++){
                    int k = 0;
                    for(k = 0; k<= j; k++){
                        toCheck[k] = text[i+k];
                    }
                    //if the previous character is not a letter or already redacted
                    if((text[i-1] < 65 && text[i-1]!='*')|| i ==0) {
                        //check through all the redacted words, adding to m as they match
                            for (int l = 0; l <= redacted - 1; l++) {
                                int m = 0;
                                //-32 is to ensure capital letters are considered
                                while (toRedact[l][m] == toCheck[m] || toRedact[l][m] - 32 == toCheck[m]) {
                                    m++;
                                }
                                //if all characters match and the last is an end character, the text should be redacted
                                if (toRedact[l][m] == '\0') {
                                    //provided the character at the end is not a letter, redact each letter
                                    for (int n = 0; n <= m - 1; n++) {
                                        if(text[i+k] <65) {
                                            text[i + n] = '*';
                                        }
                                    }
                                }
                            }

                    }
        }
    }
    /**
     * prints to command line and a file
     */
    int i = 0;
    filePointer = fopen(argv[1], "w");
    while(text[i] != '\0'){
        fputc(text[i], filePointer);
        printf("%c", text[i]);
        i++;
    }

    return 0;
}