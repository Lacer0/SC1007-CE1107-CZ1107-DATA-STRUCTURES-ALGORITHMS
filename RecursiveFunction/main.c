#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *m;

int top_down_dp(int n)
{
    if (n == 0)
    {
        m[0] = 0;
        return 0;
    }
    if (n == 1)
    {
        m[1] = 1;
        return 1;
    }
    if (n == 2)
    {
        m[2] = 2;
        return 2;
    }
    if (m[n-1] == -1)
   	    m[n-1] = top_down_dp(n-1);

    if (m[n-2] == -1)
   	    m[n-2] = top_down_dp(n-2);

    if (m[n-3] == -1)
   	    m[n-3] = top_down_dp(n-3);

    m[n] = m[n-1] + 2 * m[n-2] - 3 * m[n-3];
    return m[n];
}



int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    m = malloc(sizeof(int)*(n+1));
    for (i=0; i<=n; i++)
        m[i] = -1;
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));

}
