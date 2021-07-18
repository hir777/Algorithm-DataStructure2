#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define N 6         // Board size N x N
#define D -9        // Unreachable
#define C 8


// The 'h[x][y]' means a chess board.
// The 'h[x][y] = 0' means the grid (x, y) has not visited yet.
// The 'h[x][y]' = D' means the grid (x, y) cannot be accessed for some reasons.
// The 'h[x][y] = k' means the grid (x, y) has visited at the k step. 1 <= k <= NxN - D
int h[N][N];
int cnt = 0;         // The number of possible routes
int numD = 0;        // The number of unreachable grid
int NSQR = N * N;    // The square of N


// The 'dx[m]' and 'dy[m]' represents the way to move the knight-
// -regarding x-axis and y-axis.
// There are 8 ways in total.  0 <= m <= 7
int dx[C] = {2, 1, -1, -2, -2, -1,  1,  2};
int dy[C] = {1, 2,  2,  1, -1, -2, -2, -1};


int try(int, int, int);
void move_to(int, int, int);
void undo(int, int);
void print_knights(void);
void cpy2d(int A[N][N], int B[N][N]);


int main(void) {
    int i, j, t[N][N];
    int dddd;

    // Initialization
    for( i = 0; i < N; i++ ) {
        for( j = 0; j < N; j++ ) {
            scanf("%d", &h[i][j]);
            if( h[i][j] == D )
                numD++;
        }
    }

    cpy2d(h, t);

    // Start point (x, y) except h[x][y] == D
    for( i = 0; i < N; i++ ) {
        for( j = 0; j < N; j++ ) {

            if( h[i][j] != D ) {
                h[i][j] = 1;
                try(2, i, j);
                cpy2d(t, h);              // The board h must be made back to the original for the next iteration.
            }
        }
    }
    printf("可能な全ての巡回経路の数: %d\n", cnt);


    return 0;
}


// The function moves the knight.
// The procedure from the step 1 to the step i-1 is already recorded in the board h.
// i: the next step
// x: current x-coordinate
// y: current y-coordinate
//
// Return value
// TRUE:    succeed in finding a solution
// FALSE:   failed in finding a soultion
int try(int i, int x, int y) {
    int k = -1;
    int ok;
    int x1, y1;     // The next destination's x and y coordinate

    do {
        k++;
        ok = FALSE;
        x1 = x + dx[k];
        y1 = y + dy[k];

        // if the grid (x1, y1) has not visited yet as well as it is not unreachable.
        if( 0 <= x1 && x1 < N && 0 <= y1 && y1 < N && h[x1][y1] == 0 && h[x1][y1] != D ) {
            
            move_to(i, x1, y1);
            if( i < NSQR - numD ) {
                ok = try(i+1, x1, y1);
                if( !ok ) 
                    undo(x1, y1);   // undo the currect selection only if it results in failure     
            } else {
                ok = TRUE;
                cnt++;
                if( cnt <= 3 )
                    print_knights();      // when the solution has found.
                return ok;
            }
        }
    } while( k < C-1 );

    return ok;
}


// The function moves the knight toward the grid (x, y) at the step i.
void move_to(int i, int x, int y) {
    h[x][y] = i;
}


// The function undoes the previous step in which the knight moved toward the grid (x, y).
void undo(int x, int y) {
    h[x][y] = 0;
}


// The function prints out the board
void print_knights(void) {
    int i, j;

    printf("\n");
    for( j = 0; j < N; j++ ) {
        for( i = 0; i < N; i++ ) {
            printf("%3d", h[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}


// A: N x N matrix
// B: N x N matrix
// copy from A into B
void cpy2d(int A[N][N], int B[N][N]) {
    int i, j;

    for( i = 0; i < N; i++ ) {
        for( j = 0; j < N; j++ ) {
            B[i][j] = A[i][j];
        }
    }
}
