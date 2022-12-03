#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGHT 200;

int priorities_total_sum = 0;

int item_priority(char item) {
    int ascii = (int)item;
    int priority;
    if (ascii >= 65 && ascii <= 90) {
        priority = ascii - 65 + 27;
    } else {
        priority = ascii - 96;
    }
    
    return priority;
}

char common_item(char* str1, char* str2, char* str3, int len1, int len2, int len3) {
    for (int i = 0; i < len1; i++){
        for (int j = 0; j < len2; j++) {
            for (int k = 0; k < len3; k++){
                if ((str1[i] == str2[j]) && (str1[i] == str3[k])) {
                    return str1[i];
                }
            }
            
        }
    }
    printf("\nExited code 1, no common item!\n");
    exit(1);
}

int main() {

    FILE *fp;
    fp = (fopen("input.txt", "r"));

    int group_count = 0;
    
    char* buffer;
    size_t bufsize = MAX_LINE_LENGHT;
    buffer = (char *)malloc(bufsize * sizeof(char));

    char buf1[200];
    char buf2[200];
    char buf3[200];

    while (getline(&buffer,&bufsize,fp) != -1) {
        int cpy_len = (strlen(buffer) - 1);
        group_count++;
        switch(group_count) {
            case 1:
                memcpy(buf1, buffer, cpy_len);
                buf1[cpy_len] = '\0';
                break;
            case 2:
                memcpy(buf2, buffer, cpy_len);
                buf2[cpy_len] = '\0';
                break;
            case 3: 
                memcpy(buf3, buffer, cpy_len);
                buf3[cpy_len] = '\0';
                break;
        }
        if (group_count == 3) {
            char common = common_item(buf1, buf2, buf3, strlen(buf1), strlen(buf2), strlen(buf3));
            int priority = item_priority(common);
            priorities_total_sum = priorities_total_sum + priority;
            group_count = 0;
        }         
    }

    fclose(fp);

    printf("Result: %i\n", priorities_total_sum);

    free(buffer);
    exit(0);
}
