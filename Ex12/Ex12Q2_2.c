#include <stdio.h>
#include <math.h>

#define RAND_MAX 2147483647
#define SIGMA 1
#define MU 0
#define N 1000000

double randNPD(double *, double *);
extern void my_srand();
extern int my_GetRand();

int main() {
    int i, j, cnt[8] = {0};
    double g1, g2;

    my_srand();

    for( i = 0; i < N/2; i++ ) {
        randNPD(&g1, &g2);

        for( j = -4; j <= 3; j++ ) {
            if( MU + j * SIGMA <= g1 && g1 <= MU + (j+1) * SIGMA )
                cnt[j+4]++;
            if( MU + j * SIGMA <= g2 && g2 <= MU + (j+1) * SIGMA )
                cnt[j+4]++;
        }
    }

    for( i = -4; i <= 3; i++ )
        printf("MU + %d * SIGMA <= x <= MU + %d * SIGMA  %.3f\n", i, i+1, (double)cnt[i+4] / N);

    return 0;
}


double randNPD(double *g1, double *g2) {
    double x1, x2;

    x1 = (double)my_GetRand() / RAND_MAX;
    x2 = (double)my_GetRand() / RAND_MAX;

    *g1 = sqrt( -2.0 * log(x1) ) * cos( 2.0 * M_PI * x2 );
    *g2 = sqrt( -2.0 * log(x2) ) * sin( 2.0 * M_PI * x2 );
}
