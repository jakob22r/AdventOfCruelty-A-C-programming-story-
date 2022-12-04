#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGHT 200;

int num_pairs = 0;

int max (int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int min (int a, int b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

int main() {

    FILE *fp;
    fp = (fopen("input.txt", "r"));
    
    char* buffer;
    size_t bufsize = MAX_LINE_LENGHT;
    buffer = (char *)malloc(bufsize * sizeof(char));

    while (getline(&buffer,&bufsize,fp) != -1) {
        //Dissect on comma delimeter
        char* token1;
        char* token2;
        token1 = strtok(buffer, ",");
        token2 = strtok(NULL, ",");
        printf("Token1: %s\n", token1);       
        printf("Token2: %s\n", token2);  
        //Dissect further on - delimeter

        char* token1_low;
        char* token1_high;
        char* token2_low;
        char* token2_high;

        token1_low = strtok(token1, "-");
        token1_high = strtok(NULL, "-");

        token2_low = strtok(token2, "-");
        token2_high = strtok(NULL, "-");

        printf("Token1_low: %s\n", token1_low);       
        printf("Token1_high: %s\n", token1_high);  
        printf("Token2_low: %s\n", token2_low);       
        printf("Token2_high: %s\n", token2_high);  

        //Testing overlaps using min max logic
        //https://stackoverflow.com/questions/3269434/whats-the-most-efficient-way-to-test-if-two-ranges-overlap
        int maximum = (max(atoi(token2_high), atoi(token1_high))) - 
            (min(atoi(token2_low), atoi(token1_low)));

        int dist = (atoi(token1_high) - atoi(token1_low)) + (atoi(token2_high) - atoi(token2_low));

        //Overlap
        if (maximum <= dist) {
            num_pairs++;
        }

    }
    printf("Total: %i\n", num_pairs);

    fclose(fp);


    free(buffer);
    exit(0);
}
