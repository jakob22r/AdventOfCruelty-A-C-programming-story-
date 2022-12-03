#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGHT 200;

int priorities_total_sum = 0;

int item_priority(char item) {
    int ascii = (int)item;
    printf("Ascii val: %i\n", ascii);
    int priority;
    //Determine lower or uppercase
    if (ascii >= 65 && ascii <= 90) {
        priority = ascii - 65 + 27;
    } else {
        priority = ascii - 96;
    }
    printf("Priority val: %i\n", priority);
    


    return priority;
}

char common_item(char* str1, char* str2, int len) {
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (str1[i] == str2[j]) {
                return str1[i]; //Return common charachter
            }
        }
    }
    printf("\nExited code 1, no common item!\n");
    exit(1);

}


void main() {

    printf("Starting routine\n"); 
    int unusedvrb1 = 0; //My C crashes if they are not here, segfault...
    int unusedvrb2 = 0;

    FILE *fp;
    fp = (fopen("input.txt", "r"));

    size_t bufsize = MAX_LINE_LENGHT;
    
    char* buffer;

    while (getline(&buffer,&bufsize,fp) != -1) {
        int cpy_len = (strlen(buffer) - 1) / 2;
        char first_half[cpy_len];
        char snd_half[cpy_len];
        printf("Buffer: %s", buffer);
        printf("strlen: buf %lu\n", strlen(buffer) - 1);
        //Copy out first half of string
        memcpy(first_half, buffer, cpy_len);
        //Copy out second half of string
        memcpy(snd_half, buffer + cpy_len, cpy_len);
        first_half[cpy_len] = '\0';
        snd_half[cpy_len] = '\0';
        printf("First: %s\n", first_half);
        printf("Second: %s\n", snd_half);

        //Common charachter
        char common = common_item(first_half, snd_half, cpy_len);
        printf("Common: %c\n", common);

        //Calculate priority for found commin
        int priority = item_priority(common);
        printf("priority %i\n", priority);
        printf("\n");

        priorities_total_sum = priorities_total_sum + priority;
    }
    fclose(fp);

    printf("Total: %i\n", priorities_total_sum);
    printf("DONE!\n");

    
    exit(0);
}
