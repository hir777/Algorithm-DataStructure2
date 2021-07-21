/*

author : Hiroshi Tasaki
id     : s1270244

*/

#include <stdio.h>
#include <time.h>

/* Complete Here !! (Macro Definitions)*/
#define A 48271L
#define M 2147483647L
#define Q (M/A)
#define R (M%A)

/* Complete Here !! (Variables Declaration) */
static int B[55];
static int next = 0;
static int x = 1;       // for the next_rnd2()


int next_rnd2(void);
int next_rnd3(void);
void init_rnd(void);

int data[100];

int main() {
    int getrand, i;

    init_rnd();

    for(i = 0; i < 1000; i++) {
         getrand = next_rnd3();
         getrand %= 30;
         if( 0 <= getrand && getrand <= 29 )
             data[getrand]++;
         //printf("%d: %d\n", i + 1, getrand);
     }

    for(i=0;i<30;i++) printf("%d ",data[i]); // sample for listing outputs
    printf("\n");

    return 0;
}


void init_rnd(void) {
    int i;
    for(i = 0; i < 55; i++) /* Complete Here !! */
        B[i] = next_rnd2();
}


int next_rnd3(void) { /* Complete Here !!*/
    int i, res;

    i = (next + 31) % 55;
    res = (B[i] - B[next]);

    if( res < 0 ) {
        res += 2147483647;
        res += 1;
    }

    B[next] = res;
    next = (next + 1) % 55;
    return res;
}


int next_rnd2(void) { /* Complete Here !! */ 
    x = A * (x%Q) - R * (x/Q);
    if( x < 0 )
        x = x+M;
    return x;
}
