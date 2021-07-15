/*

author : Hiroshi Tasaki
id     : s1270244

*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


// Data structure to represent a stack
struct stack
{
    int maxsize;    // define max capacity of the stack
    int top;
    int *items;
};

 
// Utility function to initialize the stack
struct stack* newStack(int capacity)
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
 
    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (int*)malloc(sizeof(int) * capacity);
 
    return pt;
}

 
// Utility function to return the size of the stack
int size(struct stack *pt) {
    return pt->top + 1;
}

 
// Utility function to check if the stack is empty or not
int isEmpty(struct stack *pt) {
    return pt->top == -1;                   // or return size(pt) == 0;
}

 
// Utility function to check if the stack is full or not
int isFull(struct stack *pt) {
    return pt->top == pt->maxsize - 1;      // or return size(pt) == pt->maxsize;
}
 

// Utility function to add an element `x` to the stack
void push(struct stack *pt, int x)
{
    // check if the stack is already full. Then inserting an element would
    // lead to stack overflow
    if (isFull(pt))
    {
        printf("Overflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
  
    // add an element and increment the top's index
    pt->items[++pt->top] = x;
}
 

// Utility function to pop a top element from the stack
int pop(struct stack *pt)
{
    // check for stack underflow
    if (isEmpty(pt))
    {
        printf("Underflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
  
    // decrement stack size by 1 and (optionally) return the popped element
    return pt->items[pt->top--];
}


int main(int args, char *argv[]) {
    int **dp, n, b, i, j, k, *a;
    FILE *fp;

    fp = fopen(argv[1], "r");
    fscanf(fp, "%d %d", &n, &b);

    a = (int *)malloc( sizeof(int) * n );
    for( i = 0; i < n; i++ )
        fscanf(fp, "%d", &a[i]);

    dp = (int **)malloc( sizeof(int *) * (n+1) );
    for( i = 0; i < n+1; i++ ) {
        dp[i] = (int *)malloc( sizeof(int) * (b+1) );

        for( j = 0; j <= b; j++ )
            dp[i][j] = FALSE;       // Initialize the all elements with false
    }
    dp[0][0] = TRUE;                // Since the sum of zero positive integers is zero, dp[0][0] should be 'TRUE'.

    for( i = 0; i < n; i++ ) {
        for( j = 0; j <=b; j++ ) {
            dp[i+1][j] = dp[i][j] || dp[i+1][j];
            if( j >= a[i] )
                dp[i+1][j] = dp[i][j-a[i]] || dp[i+1][j];
        }
    }

    struct stack *_stack = newStack(n+1);

    if( dp[n][b] ) {
        printf("YES\n");

        for( i = n, j = b; i >= 1; i-- ) {
            if( dp[i][j] == TRUE && dp[i-1][ j ] == FALSE ) {
                //printf("%d ", a[i-1]);
                push(_stack, a[i-1]);
                j -= a[i-1];
            }
        }
        
        for( i = size(_stack); i > 0; i-- )
            printf("%d ", pop(_stack));
        printf("\n");

    }
    else
        printf("NO\n");

    return 0;
}
