/*

author : Hiroshi Tasaki
id     : s1270244

*/


#include <stdio.h>
#include <stdlib.h>

#define INFTY 99999
#define MIN(a,b) (((a)<(b))?(a):(b))

int Floyd(int, int, int);

int main() {
    int i, j, k;
    int minDist = INFTY, maxDist = 0;
    int minVertex1, minVertex2;         // 最も距離の短い頂点対
    int maxVertex1, maxVertex2;         // 最も距離の長い頂点対

    int **Data, n;

    /* input data (size) */
    printf("Input the number of data: ");
    scanf("%d", &n);

    /* Generate arrays (memory allocation)*/
    Data = (int **)malloc(n * sizeof(int *));

    for(i = 0; i < n; i++) {
        Data[i] = (int *)malloc(n * sizeof(int));
    }

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
            if( Data[i][j] < minDist ) {
                minDist = Data[i][j];
                minVertex1 = i;
                minVertex2 = j;
            }
            
            if( Data[i][j] > maxDist ) {
                maxDist = Data[i][j];
                maxVertex1 = i;
                maxVertex2 = j;
            }
        }
    }

    printf("min: %d  (%d, %d)\n", minDist, minVertex1+1, minVertex2+1);
    printf("max: %d  (%d, %d)\n", maxDist, maxVertex1+1, maxVertex2+1);
     
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

    Dk_ij = MIN( D_ij, D_ik + D_kj);

    return Dk_ij;
}
