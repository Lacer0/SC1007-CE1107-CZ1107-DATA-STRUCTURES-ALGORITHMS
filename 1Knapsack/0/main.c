#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int **m;

int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));

    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);

    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);

    m = (int**) malloc(sizeof(int*)* (n+1));
    for (i=0; i<=n; i++)
        m[i] = (int*) malloc(sizeof(int)* (C+1));
    for (i=0; i<=n; i++)
    {
        for(j=0; j<=C; j++)
            m[i][j] = 0;
    }
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));

}


int bottom_up_dp(int n, int *s, int *v, int C)
{
    int temp;

    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=C; j++)
        {
            if (j-s[i]<0)
                m[i][j] = m[i-1][j];
            else
            {
                temp = m[i-1][j-s[i]] + v[i];
                m[i][j] = (temp > m[i-1][j]) ? temp : m[i-1][j];
            }
        }
    }
    return m[n][C];
}
