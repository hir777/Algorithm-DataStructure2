/*

author : Hiroshi Tasaki
id     : s1270244

*/


#include <stdio.h>
#include <stdlib.h>

#define INFTY 99999

int Warshall(int, int, int);

int main() {
    int i, j, k;

    int **Data, n;
    int isIsolated;

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
                Data[i][j] = Warshall(Data[i][j], Data[i][k], Data[k][j]);      // Warshall's Algorithm
            }
        }
    }
    // end 3-level nested loop

    for( j = 0; j < n; j++ ) {

        isIsolated = 1;
        for( i = 0; i < n; i++ ) {

            if( Data[i][j] != 0 ) {
                isIsolated = 0;
                break;
            }
        }

        if( isIsolated == 1 )
            printf("Vertex %d is the one isolated from the other vertices in the graph.\n", j+1);
    }

    /* free allocated memory*/
    for(i = 0; i < n; i++) {
        free(Data[i]);
    }
    free(Data);

    return 0;
}

/* Kernel process of Floyd's & Warshall's Algorithm */

int Warshall(int A_ij, int A_ik, int A_kj) {
    /* Arguments A_ij, A_ik, A_kj means A^{k-1}[i][j], A^{k-1}[i][k],A^{k-1}[k][j] at the pseudo code. */
    int Ak_ij; /* A^k[i][j] */

    Ak_ij = A_ij || ( A_ik && A_kj );

    return Ak_ij;
}
