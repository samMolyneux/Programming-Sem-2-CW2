#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE *filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("no file found");
    }
    char nextChar = fgetc((FILE *) filePointer);
    char text[8192] = {};
    int counter = 0;
    while(nextChar != EOF){
        text[counter] = nextChar;
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

    int redacted = 1;
    int maxRedacted = 1;
    char toRedact[redacted][maxRedacted];
    toRedact[0][0] = 'a';
    char toCheck[maxRedacted];

    for(int i = 0; i <= 8191; i++){
        *toCheck = text[i];
        for(int j = 0; j <= maxRedacted-1; j++){
                    int k = 0;
                    for(k = 0; k<= j; k++){
                        toCheck[k] = text[i+k];
                    }
                    for(int l = 0; l <= redacted-1;l++){
                        int m = 0;
                        while(toRedact[l][m] == toCheck[m]){
                            m++;
                        }
                        if(m == maxRedacted -1){
                            for(int n = 0; n <= k; n++){
                                text[i + n] = '*';
                                printf("redacting");
                            }
                        }
                    }
        }

    }
    return 0;
}