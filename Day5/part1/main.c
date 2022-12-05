#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGHT 200;

//Taken from stackoverflow
char *strrev(char *str)
{
    char *end, *wrk = str;
    {
        if(str && *str)
        {
            end = str + strlen(str) - 1;
            while(end > wrk)
            {
                char temp;

                temp = *wrk;
                *wrk++ = *end;
                *end-- = temp;
            }
        }
    }
    return str;
}

struct stack {
    int maxsize;
    char stack[200];
    int top; //Index for the top
};

struct stack* controlarr[9]; //Array containing char pointers to the different stacks

struct stack* stack_init() {
    char arr[200];
    struct stack* stack = (struct stack*)malloc(sizeof(struct stack));
    stack->maxsize = MAX_LINE_LENGHT;
    memcpy(stack->stack, arr, sizeof(arr));
    stack->top = -1;
    return stack;
}

void init_stacks() {
    for (int i = 0; i < 9; i++) {
        struct stack* stack = stack_init();
        controlarr[i] = stack; //Adding stackpointer to control array
    }
}

void destroy_stacks() {
    for (int i = 0; i < 9; i++) {
        free(controlarr[i]);
    }
}

void print_stack(int stack_index) {
    for (int i = 0; i <= controlarr[stack_index]->top; i++) {
        printf("%c", controlarr[stack_index]->stack[i]);
    }
    printf("\nTop-index: %i\n", controlarr[stack_index]->top);
    printf("Top-elem: %c\n", controlarr[stack_index]->stack[controlarr[stack_index]->top]);    
}

void print_all_stacks() {
    for (size_t i = 0; i < 3; i++)
    {
        print_stack(i);
    }
    
}

//push onto proper stack
void push(char elem, int stack_index) {
    controlarr[stack_index]->top++;
    controlarr[stack_index]->stack[controlarr[stack_index]->top] = elem; //Insert elem on top
}

char pop(int stack_index) {
    char popped = controlarr[stack_index]->stack[controlarr[stack_index]->top];
    controlarr[stack_index]->top--;
    return popped;
}


void reverse_all_stacks() {
    for (int i = 0; i < 9; i++) {
        //Reverse stack items
        char* rev = strrev(controlarr[i]->stack);
        memcpy(controlarr[i]->stack, rev, sizeof(controlarr[i]->stack));

        //Set top index properly
        controlarr[i]->top = strlen(controlarr[i]->stack)-1;
    }
}

void move(int amount, int from, int to) {
    
    for (int i = 0; i < amount; i++)
    {
        char popped = pop(from-1); //+1 to correct 1-indexing in assignment
        push(popped, to-1);
    }
    
}

int main() {

    init_stacks();

    char* buffer0;
    size_t bufsize0 = MAX_LINE_LENGHT;
    buffer0 = (char *)malloc(bufsize0 * sizeof(char));
    FILE *fp0;
    fp0 = (fopen("setup2.txt", "r"));
    while (getline(&buffer0,&bufsize0,fp0) != -1) {
        for (size_t i = 0; i < strlen(buffer0); i++)
        {
            if ((int)buffer0[i] >= 65 && (int)buffer0[i] <= 90) {
                int stack_index = (i-1) / 4; //Calculates index in range 0-8
                push(buffer0[i], stack_index); //Push onto stack
            }
        }
    }
    reverse_all_stacks();
    
    fclose(fp0);   
    free(buffer0); 



    FILE *fp;
    fp = (fopen("input2.txt", "r"));
    
    char* buffer;
    size_t bufsize = MAX_LINE_LENGHT;
    buffer = (char *)malloc(bufsize * sizeof(char));

    while (getline(&buffer,&bufsize,fp) != -1) {
        int amount;
        int from;
        int to;
        sscanf(buffer, "move %d from %d to %d", &amount, &from, &to);
        move(amount, from, to);
    }

    printf("Result:\n");
    for (size_t i = 0; i < 9; i++)
    {
        printf("%c",controlarr[i]->stack[controlarr[i]->top]);
    }
    printf("\n");

    fclose(fp);

    free(buffer);
    destroy_stacks(); //Free memory
    exit(0);
}
