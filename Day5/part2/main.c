#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>

#define MAX_LINE_LENGHT 200;

int num_stacks = 9;

//Taken from stackoverflow
char *strrev(char *str)
{
    if (!str || ! *str)
        return str;

    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
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
    for (int i = 0; i < num_stacks; i++) {
        struct stack* stack = stack_init();
        controlarr[i] = stack; //Adding stackpointer to control array
    }
}

void destroy_stacks() {
    for (int i = 0; i < num_stacks; i++) {
        free(controlarr[i]);
    }
}

void print_stack(int stack_index) {
    printf("---PRINTING STACK %i---\n", stack_index);
    printf("Top-index: %i\n", controlarr[stack_index]->top);
    printf("Top-elem: %c\n", controlarr[stack_index]->stack[controlarr[stack_index]->top]); 
    for (int i = 0; i <= controlarr[stack_index]->top; i++) {
        printf("%c", controlarr[stack_index]->stack[i]);
    }   
    printf("\n---------------\n");
}

void print_all_stacks() {
    for (int i = 0; i < num_stacks; i++)
    {
        print_stack(i);
    }
    
}

void push(char elem, int stack_index) {
    controlarr[stack_index]->top++;
    controlarr[stack_index]->stack[controlarr[stack_index]->top] = elem; //Insert elem on top
    controlarr[stack_index]->stack[controlarr[stack_index]->top+1] = '\0';
}

char pop(int stack_index) {
    if (controlarr[stack_index]->top >= 0) {
        char popped = controlarr[stack_index]->stack[controlarr[stack_index]->top];
        controlarr[stack_index]->top--;
        return popped;
    } else {
        printf("CANNOT POP FROM EMPTY STACK!\n");
    }
    
}

void reverse_all_stacks() {
    for (int i = 0; i < num_stacks; i++) {
        //Reverse stack items
        char* rev = strrev(controlarr[i]->stack);
        memcpy(&controlarr[i]->stack, rev, sizeof(controlarr[i]->stack));

        //Set top index properly
        controlarr[i]->top = strlen(controlarr[i]->stack)-1;
    }
}

void move(int amount, int from, int to) {

    if (amount > 1) {
        char tmp[amount+1]; //Temporary array to store popped elems
        for (int i = 0; i < amount; i++)
        {
            char popped = pop(from-1); //+1 to correct 1-indexing in assignment
            tmp[i] = popped;
        }
        tmp[amount] = '\0';
        
        //Reverse string and push elemwise
        char* rev = strrev(tmp);
        rev[amount] = '\0';
        for (int i = 0; i < amount; i++)
        {
            push(rev[i], to-1);
        }
    } else { //Same behaviour as in part 1
        for (int i = 0; i < amount; i++)
        {
            char popped = pop(from-1); //+1 to correct 1-indexing in assignment
            push(popped, to-1);
        }
    }
}

int main() {

    init_stacks();

    char* buffer0;
    size_t bufsize0 = MAX_LINE_LENGHT;
    buffer0 = (char *)malloc(bufsize0 * sizeof(char));
    FILE *fp0;
    fp0 = (fopen("setup.txt", "r"));
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
    print_all_stacks();
    
    fclose(fp0);   
    free(buffer0); 



    FILE *fp;
    fp = (fopen("input.txt", "r"));
    
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
    for (size_t i = 0; i < num_stacks; i++)
    {
        printf("%c",controlarr[i]->stack[controlarr[i]->top]);
    }
    printf("\n");

    fclose(fp);

    free(buffer);
    destroy_stacks(); //Free memory
    exit(0);
}
