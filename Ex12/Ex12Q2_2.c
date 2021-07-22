#include <stdio.h>
#include <math.h>

#define RAND_MAX 2147483647
#define SIGMA 1
#define MU 0
#define N 500000

void randNPD(double *, double *);
extern void my_srand();
extern int my_GetRand();

int main() {
    int i, j, upper, lower;
    int cnt[8] = {0};
    double g1, g2;

    my_srand();

    for( i = 0; i < N; i++ ) {
        randNPD(&g1, &g2);

        for( j = -4; j <= 3; j++ ) {
            lower = MU + j * SIGMA;
            upper = MU + (j+1) * SIGMA;
            if( lower <= g1 && g1 <= upper )
                cnt[j+4]++;
            if( lower <= g2 && g2 <= upper )
                cnt[j+4]++;
        }
    }

    for( i = -4; i <= 3; i++ ) {
        printf("MU + %3d * SIGMA <= x <= MU + %3d * SIGMA  cnt : %8d  rate: %.3f %%\n", i, i+1, cnt[i+4], ((double)cnt[i+4] / (N*2)) * 100 );
    }

    return 0;
}


// The function produces normal-distribution based-random numbers
// At each invocation of this function, it creates the two random numbers.
void randNPD(double *g1, double *g2) {
    double x1, x2;

    x1 = (double)my_GetRand() / RAND_MAX;
    x2 = (double)my_GetRand() / RAND_MAX;

    *g1 = sqrt( -2.0 * log(x1) ) * cos( 2.0 * M_PI * x2 );
    *g2 = sqrt( -2.0 * log(x1) ) * sin( 2.0 * M_PI * x2 );
}
