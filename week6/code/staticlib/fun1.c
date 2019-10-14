
int max(int *a,int n)
{
    int i = 0,max = 0;
    for ( i = 0; i < n; i++)
    {
        if (max < a[i])
        {
            max = a[i];
        }
        
    }
    return max;
}
