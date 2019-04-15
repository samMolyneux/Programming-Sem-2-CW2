#include <stdio.h>

#define maxChar 5
int main(int argc, char *argv[]) {

    FILE *filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("no file found");
    }
    char nextChar = fgetc((FILE *) filePointer);
    char text[8192] = {};
    int counter = 0;
    while(nextChar != EOF){
        //text[counter] = nextChar;
        //printf("%c",text[counter]);

        counter++;
        nextChar = fgetc((FILE *) filePointer);
    }
    fclose(filePointer);
    int i = 0;
    while(argv[2][i]!= '\0'){
        text[i]=argv[2][i];
        printf("%c",text[i]);
        i++;
    }
    text[i] = '\0';

    int redacted = 2;
    int maxRedacted = 5;
    char toRedact[redacted][maxRedacted];

    toRedact[0][0] = 'a';
    toRedact[0][1] = 'b';
    toRedact[0][2] = '\0';

    toRedact[1][0] = 'c';
    toRedact[1][1] = '\0';
    char toCheck[maxRedacted];
    printf("\n");
    //65 - 172
    for(int i = 0; i <= maxChar; i++){
        *toCheck = text[i];
        for(int j = 0; j <= maxRedacted-1; j++){
                    int k = 0;
                    for(k = 0; k<= j; k++){
                        toCheck[k] = text[i+k];
                    }
                    if((text[i-1] < 65 && text[i-1]!='*')|| i ==0) {
                            for (int l = 0; l <= redacted - 1; l++) {
                                int m = 0;
                                while (toRedact[l][m] == toCheck[m] || toRedact[l][m] - 32 == toCheck[m]) {
                                    // printf("\n%c", toRedact[l][m]);
                                    m++;
                                }
                                if (toRedact[l][m] == '\0') {
                                    for (int n = 0; n <= m - 1; n++) {
                                        // printf("starts at :%d\n",i);
                                        printf("redacting: %c at pos %d\n", text[i + n], i + n);
                                        if(text[i+k+1] <65) {
                                            text[i + n] = '*';
                                        }
                                    }
                                }
                            }

                    }
        }
    }
    i = 0;
    while(text[i] != '\0'){
        printf("%c", text[i]);
        i++;
    }

    return 0;
}