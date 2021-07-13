#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define NUM 5           // The 'NUM' types of coins are given for a payment.


int pay(int *, int);


int main(void) {
    int payment;        // It corresponds to the amount of payment needed to be payed with the minimum number of coin.
    int t;
    int coins[NUM] = {1, 5, 10, 17, 25};

    printf("Payment ->");
    scanf("%d", &payment);

    t = pay(coins, payment);
    printf("Result: %d \n", t);

    return 0;
}


// This function calculates the combination of the given coins for-  
// the paymentson condition that the minimum number of coins is requred.
//
// Input  ->  coins: The array contains the types of coins.    
//          The coins are stored in the ascending order in terms of their amount
//
// Output ->  The minimum number of coins needed for 'payment'
int pay(int *coins, int payment) {
    int i, j, *p;      // The p[k] element stores the possible minimum number of coins to pay for k yen.

    p = (int *)malloc( sizeof(int) * ( payment + 1 ) );

    // Initilization
    for( i = 0; i<=payment; i++ )
        p[i] = INT_MAX;
    for( i = 0; i < p[0]; i++ )
        p[i] = 0;
    for( i = 0; i < NUM; i++ )
        p[ coins[i] ] = 1;

    // Solve the problem by the dynamic programming
    for( i = coins[0]; i <= payment; i++ ) {

        for( j = 0; j < NUM; j++ ) {

            if( i + coins[j] > payment )
                continue;

            if(  p[i] == INT_MAX )
                break;

            if( p[ i + coins[j] ] > p[i] + 1 )
                p[ i + coins[j] ] = p[i] + 1;
        }
    }

    return p[payment];
}
