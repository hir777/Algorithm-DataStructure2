/*

author : Kimura Kaisei
id     : s1260070

*/

#include <stdio.h>
#include <math.h>
extern void my_srand();
extern int my_GetRand();

#define RAND_MAX 2147483647.0
#define TOTAL 500000

int main(){
    int i, j, cnt[8];
    double x1, x2, g1, g2;
    
    my_srand();
    
    for(i = 0; i < 8; i++){
        cnt[i] = 0;
    }

    for(i = 0; i < TOTAL; i++){
        x1 = my_GetRand() / RAND_MAX;
        x2 = my_GetRand() / RAND_MAX;
        g1 = sqrt(-2 * log(x1)) * cos(2 * M_PI * x2);
        g2 = sqrt(-2 * log(x1)) * sin(2 * M_PI * x2);
    
        for(j = -4; j < 4; j++){
            if(j <= g1 && g1 <= j + 1)
                cnt[j + 4]++;
            if(j <= g2 && g2 <= j + 1)
                cnt[j + 4]++;
        }
        
    }
    
    for(i = 0; i < 8; i++){
        double pro = (double)cnt[i]/(TOTAL*2);
        printf("Times:%d < x < %d: %d Proportion:[%6.3lf]\n", i - 4, i - 3, cnt[i],pro*100);
    }
}
