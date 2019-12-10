
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

void show(int *j, int n) //show randnum
{
    int i;
    printf("randnum: ");
    for ( i = 0; i < n; i++)
    {
        printf("a[%d] %d\n",i,j[i]);
    }
}
