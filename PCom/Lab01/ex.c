#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Stack { 
    int top; 
    int capacity; 
    char * array; 
} TStack; 

TStack *createStack(int capacity) 
{ 
    TStack* stack = (TStack *)malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (char *)malloc(stack->capacity * sizeof(char));
    return stack; 
} 

int isFull(struct Stack* stack) 
{ 
    return stack->top == stack->capacity - 1; 
}
 
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1; 
} 
  
void push(struct Stack* stack, char item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
} 
  
char pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return 0;
    return stack->array[stack->top--]; 
} 

void send_error(char *message) {
    perror(message);
    exit(1);
}

int main(int argc, char *argv[]) {
    

    int i = 1;
    printf("\n=== CAT ===\n");
    for(; i < argc; i++) {
        int fd_in;
        int valid_input;
        char buffer[1];
        printf("\n=== Se afiseaza fisierul cu numele \"%s\" si nr. %d ===\n", argv[i], i);
        fd_in = open(argv[i], O_RDONLY);

        if(fd_in < 0) {
         send_error("can't open input file for CAT");
        }

        while((valid_input = read(fd_in, buffer, sizeof(buffer)))) {
            if(valid_input < 0) {
              send_error("can't read for CAT");
            }
            printf("%s", buffer);
        }

        close(fd_in);
    }
    
    i = 1;
    printf("\n=== TAC ===\n");
    for(; i < argc; i++) {
        int fd_in;
        int valid_input;
        char buffer[1];
        printf("\n=== Se afiseaza fisierul cu numele \"%s\" si nr. %d ===\n", argv[i], i);
        fd_in = open(argv[i], O_RDONLY);
        TStack *stack = createStack(1024);
        int length = 0;

        if(fd_in < 0) {
            send_error("can't open input file for TAC");
        }

        while((valid_input = read(fd_in, buffer, sizeof(buffer)))) {
            if(valid_input < 0) {
              send_error("can't read for TAC");
            }
            push(stack, buffer[0]);
            length++;
        }

        int j = 0;
        for(; j < length; j++){
            char c = pop(stack);
            printf("%c", c);
        }

        close(fd_in);
    }

    printf("\n");
    return 0;
}