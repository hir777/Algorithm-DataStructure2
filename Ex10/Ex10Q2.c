/*

author : Hiroshi Tasaki
id     : s1270244

*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

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

    if( dp[n][b] ) {
        printf("YES\n");

        for( i = n, j = b; i >= 1; i-- ) {
            if( dp[i][j] == TRUE && dp[i-1][ j ] == FALSE ) {
                printf("%d ", a[i-1]);
                j -= a[i-1];
            }
        }
        printf("\n");
    }
    else
        printf("NO\n");

    return 0;
}
