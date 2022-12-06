#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>

#define MAX_LINE_LENGHT 8196;

char* buf;

int main() {


    size_t bufsize = MAX_LINE_LENGHT;
    buf = (char *)malloc(bufsize * sizeof(char));
    FILE *fp;
    fp = (fopen("input.txt", "r"));
    while (getline(&buf,&bufsize,fp) != -1) {
        size_t cnt = 3;
        //Extract substrings
        while(cnt < strlen(buf)) {
            printf("i = %i\n", cnt);
            char sub[5]; //Space for null termination

            //At cnt we take a substring from [cnt-3 ; cnt]
            strncpy(sub, &(buf[cnt-3]), 4);
            cnt++;
            
            //used to break out of outer loop if there is a mismatch in the substring
            int nomatch = 0;
            //Now check if items are unique
            for (size_t i = 0; i < 4; i++)
            {
                for (size_t j = 0; j < 4; j++)
                {
                    if(sub[i] == sub[j] && i != j) {
                        nomatch = 1;
                        break;
                    } else if (i == 3 && j == 3) {
                        printf("RESULT FOUND: [%s] at: %i\n", sub, cnt);
                        exit(0);
                    }
                }
                if (nomatch == 1) {
                    break;
                }
                
            }
        }   
    }
    
    fclose(fp);   
    free(buf); 

    exit(0);
}
