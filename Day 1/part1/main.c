#include <stdlib.h>
#include <stdio.h>

int main() {

    int max_cal = 0;
    int current_cal = 0;

    FILE *fp;
    fp = (fopen("input.txt", "r"));

    char* buffer;
    size_t bufsize = 100;
    
    while (getline(&buffer,&bufsize,fp) != -1) {
        if (buffer[0] == '\n') {
            if (current_cal > max_cal) {
                max_cal = current_cal;
            }
            current_cal = 0;
        }
        current_cal = current_cal + atoi(buffer);
    }
    printf("Max_cal: %i\n", max_cal);
    fclose(fp);
    return max_cal;
}

