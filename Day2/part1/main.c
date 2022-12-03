#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGHT 5;

int total_score;

//Points awarded for choosing sign
int item_points(char player) {
    if (player == 'X') {
        return 1;
    } else if (player == 'Y') {
        return 2;
    } else {
        return 3;
    }
}

//Internal representation for use in algorithm
int internal_rep (char player) {
    if (player == 'X' || player == 'A') {
        return 0;
    } else if (player == 'Y' || player == 'B') {
        return 1;
    } else {
        return 2;
    }
}

//Using internal representation to calculate who has won 
int round_points(int opp, int me) {
    if ((opp + 1) % 3 == me) {
        //I won
        return 6;
    } else if (opp == me) {
        //Draw
        return 3;
    } else { 
        //Opponent won
        return 0;
    }
}


int main() {

    printf("Starting routine\n"); 
    int unusedvrb1 = 0; //My C crashes if they are not here, segfault...
    int unusedvrb2 = 0;

    FILE *fp;
    fp = (fopen("input.txt", "r"));

    char* buffer;
    size_t bufsize = MAX_LINE_LENGHT;
    
    while (getline(&buffer,&bufsize,fp) != -1) {
        char opp = buffer[0];
        char me = buffer[2];
        printf("---ROUND---\n");
        printf("opp: %c, me %c\n", opp, me);

        int internal_rep_opp = internal_rep(opp);
        int internal_rep_me = internal_rep(me);

        int item_point = item_points(me);
        int round_score = round_points(internal_rep_opp, internal_rep_me);

        printf("Internal_rep_opp: %i\n", internal_rep_opp);
        printf("internal_rep_me: %i\n", internal_rep_me);
        printf("Item Point: %i\n", item_point);
        printf("Round score: %i\n", round_score);
        printf("Item Point: %i\n", item_point);
        printf("Round score: %i\n", round_score);

        int round_total;
        round_total = item_point + round_score;
        printf("Round total: %i\n", round_total);
        
        total_score = total_score + round_total;

        printf("Total score: %i\n\n", total_score);
    }
    fclose(fp);
    return 0;
}
