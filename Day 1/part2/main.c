#include <stdlib.h>
#include <stdio.h>

int main() {

    int max_cal1 = 0;
    int max_cal2 = 0;
    int max_cal3 = 0;
    
    int current_cal = 0;

    FILE *fp;
    fp = (fopen("input.txt", "r"));

    char* buffer;
    size_t bufsize = 100;
    
    while (getline(&buffer,&bufsize,fp) != -1) {
        if (buffer[0] == '\n') {
            printf("Newline!\n");
            if (current_cal > max_cal1) {
                max_cal1 = current_cal;
            } else if (current_cal > max_cal2) {
                max_cal2 = current_cal;
            } else if (current_cal > max_cal3) {
                max_cal3 = current_cal;
            }
            current_cal = 0;
        }
        printf("Current cal before: %i\n", current_cal);
        current_cal = current_cal + atoi(buffer);
        printf("Current cal after: %i\n", current_cal);
        printf("Max_cal: %i\n", max_cal1);
    }

    int total = max_cal1 + max_cal2 + max_cal3;
    printf("Total: %i\n", total);

    fclose(fp);
    return 0;
}

