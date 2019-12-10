#include <stdlib.h>
void urand(int *a, int n) //0-100 n ge suijishu
{   
    int i = 0;
    srand((int)time(0));
    for ( i = 0; i < n; i++)
    {
        a[i] = 1+(int)(100.0*rand()/(RAND_MAX+1.0));
    } 
}
