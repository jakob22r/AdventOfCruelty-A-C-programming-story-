#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGHT 5;

int total_score;

//Points awarded for choosing sign
int item_points(int player) {
    if (player == 0) {
        return 1;
    } else if (player == 1) {
        return 2;
    } else {
        return 3;
    }
}

//Internal representation for use in algorithm, Basically converts char to a number
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

//Choses correct strategy, and returns proper symbol
int choose_sign(int opp_int, int me_int) {
    if (me_int == 1) { //If Y (paper = 1) we want a draw
        return opp_int;
    } else if (me_int == 2) { //Z, so we want to win
        return (opp_int + 1) % 3;
    } else {
         if (opp_int == 0) {
            return 2; //Easy way avoiding having to think about more modular arithmetic
         } else {
            return opp_int - 1;
         }
    }
}

int main() {
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

        //I have to figure out what to do according to strategy
        int new_sign_me = choose_sign(internal_rep_opp, internal_rep_me);
       
        printf("Internal_rep_opp: %i\n", internal_rep_opp);
        printf("new_sign_me: %i\n", new_sign_me);

        int item_point = item_points(new_sign_me);
        int round_score = round_points(internal_rep_opp, new_sign_me);

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
