int sum(int *a,int n)
{
    int i = 0,sum = 0;
    for ( i = 0; i < n; i++)
    {
        sum += a[i];        
    }
    return sum;
}