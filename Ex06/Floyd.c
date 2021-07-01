/*

author : Hiroshi Tasaki
id     : s1270244

*/


#include <stdio.h>
#include <stdlib.h>

#define INFTY 99999
#define MIN(a,b) (((a)<(b))?(a):(b))

#define MAX_NUM 50      // the maximum number of stuck elements

int Floyd(int, int, int);

// A structure to represent an edge
struct Edge {
    int i, j;       // edge (i, j)
    int weight;
};

// A structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    struct Edge* array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Edge*)malloc(stack->capacity * sizeof(struct Edge));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, struct Edge item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
struct Edge pop(struct Stack* stack)
{
    struct Edge err;
    err.i = -1;
    err.j = -1;
    err.weight = -1;

    if (isEmpty(stack))
        return err;
    return stack->array[stack->top--];
}

int main() {
    int i, j, k;
    int preVal;
    struct Stack *minStack, *maxStack;
    struct Edge min, max;

    int **Data, n;

    max.weight = 0;
    min.weight = INFTY;

    /* input data (size) */
    printf("Input the number of data: ");
    scanf("%d", &n);

    /* Generate arrays (memory allocation)*/
    Data = (int **)malloc(n * sizeof(int *));

    for(i = 0; i < n; i++) {
        Data[i] = (int *)malloc(n * sizeof(int));
    }

    // Create stack
    minStack = createStack(MAX_NUM);
    maxStack = createStack(MAX_NUM);

    /* input data (matrix)*/
    printf("Input the Adjacency or Distance matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &Data[i][j]);
        }
    }

    /* Main routines */
    /* [ Complete Here!! ( 3-level nested loop) ] */

    /* Call main routines */
     for( k = 0; k < n; k++ ) {
        for( i = 0; i < n; i++ ) {
            for( j = 0; j < n; j++ ) {
                Data[i][j] = Floyd(Data[i][j], Data[i][k], Data[k][j]);     // Floyd's Algorithm
            }
        }
    }
    // end 3-level nested loop

    for( i = 0; i < n; i++ ) {
        for( j = 0; j < n; j++ ) {
            if( Data[i][j] <= min.weight ) {
                min.i = i;
                min.j = j;
                min.weight = Data[i][j];
                push(minStack, min);
            }
            
            if( Data[i][j] > max.weight ) {
                max.i = i;
                max.j = j;
                max.weight = Data[i][j];
                push(maxStack, max);
            }
        }
    }

    int stackSize = minStack->top;

    // print the edges with the min weight
    for( i = 0; i <= stackSize; i++ ) {
        min = pop(minStack);
        
        if( i == 0 )
            preVal = min.weight;
        if( preVal < min.weight )
            break;
        printf("min: %d  (%d, %d)\n", min.weight, min.i+1, min.j+1);
        preVal = min.weight;
    }

    stackSize = maxStack->top;
    // print the edges with the max weight
    for( i = 0; i <= stackSize; i++ ) {
        max = pop(maxStack);

        if( i == 0 )
            preVal = max.weight;
        if( preVal > max.weight )
            break;
        printf("max: %d  (%d, %d)\n", max.weight, max.i+1, max.j+1);
        preVal = max.weight;
    }
     
    /* free allocated memory*/
    for(i = 0; i < n; i++) {
        free(Data[i]);
    }
    free(Data);

    return 0;
}

int Floyd(int D_ij, int D_ik, int D_kj) {
    /* Arguments D_ij, D_ik, D_kj means D^{k-1}[i][j], D^{k-1}[i][k],D^{k-1}[k][j] at the pseudo code. */
    int Dk_ij; /* D^k[i][j] */

    Dk_ij = MIN( D_ij, D_ik + D_kj );

    return Dk_ij;
}