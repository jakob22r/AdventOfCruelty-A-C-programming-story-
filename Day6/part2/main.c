#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>

#define MAX_LINE_LENGHT 8196;

size_t char_procesed = 14;

char* buf;

int main() {


    size_t bufsize = MAX_LINE_LENGHT;
    buf = (char *)malloc(bufsize * sizeof(char));
    FILE *fp;
    fp = (fopen("input.txt", "r"));
    while (getline(&buf,&bufsize,fp) != -1) {
        size_t cnt = char_procesed - 1;
        //Extract substrings
        while(cnt < strlen(buf)) {
            char sub[char_procesed + 1]; //Space for null termination

            //At cnt we take a substring from [cnt-3 ; cnt]
            strncpy(sub, &(buf[cnt - (char_procesed -1)]), char_procesed);
            cnt++;
            
            //used to break out of outer loop if there is a mismatch in the substring
            int nomatch = 0;
            //Now check if items are unique
            for (size_t i = 0; i < char_procesed; i++)
            {
                for (size_t j = 0; j < char_procesed; j++)
                {
                    if(sub[i] == sub[j] && i != j) {
                        nomatch = 1;
                        break;
                    } else if (i == char_procesed - 1 && j == char_procesed - 1) {
                        printf("RESULT FOUND: [%s] at: %zu\n", sub, cnt);
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
