/*

author : Hiroshi Tasaki
id     : s1270244

*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


int main(int args, char *argv[]) {
    int **dp, n, b, i, j, k, *a, **cnt, t;
    FILE *fp;

    fp = fopen(argv[1], "r");
    fscanf(fp, "%d %d", &n, &b);

    a = (int *)malloc( sizeof(int) * n );
    for( i = 0; i < n; i++ )
        fscanf(fp, "%d", &a[i]);

    // Secure memory spaces for the dp and initialize it.
    dp = (int **)malloc( sizeof(int *) * (n+1) );
    for( i = 0; i < n+1; i++ ) {
        dp[i] = (int *)malloc( sizeof(int) * (b+1) );

        for( j = 0; j <= b; j++ )
            dp[i][j] = FALSE;       // Initialize the all elements with false
    }
    dp[0][0] = TRUE;                // Since the sum of zero positive integers is zero, dp[0][0] should be 'TRUE'.

    // Secure memory spaces for the cnt and initialize it.
    cnt = (int **)malloc( sizeof(int *) * (n+1) );
    for( i = 0; i < n+1; i++ ) {
        cnt[i] = (int *)malloc( sizeof(int) * (b+1) );

        for( j = 0; j <= b; j++ ) {
            cnt[i][j] = 0;
        }
    }
    cnt[0][0] = 1;

    for( i = 0; i < n; i++ ) {
        for( j = 0; j <=b; j++ ) {

            t = 0;
            if( j >= a[i] && dp[i][ j-a[i] ] == TRUE ) {
                dp[i+1][j] = TRUE;
                cnt[i+1][j] = cnt[i][ j-a[i] ];
                t += 1;
            }
            if( j + a[i] <= b && dp[i][ j+a[i] ] == TRUE ) {
                dp[i+1][j] = TRUE;
                cnt[i+1][j] = cnt[i][ j+a[i] ];
                t += 1;
            }
            if( t == 2 )
                cnt[i+1][j] = cnt[i][ j-a[i] ] + cnt[i][ j+a[i] ];
        }
    }


    if( dp[n][b] ) {
        printf("YES\nPossible pattern = %d\n", cnt[n][b]);
    }
    else
        printf("NO\n");

    return 0;
}
