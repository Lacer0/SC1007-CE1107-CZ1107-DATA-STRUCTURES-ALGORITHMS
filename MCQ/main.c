#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("%d",A5Q(8,8));
    return 0;
}

int A5Q(int X, int N)
{
    int HALF;

    if (N==1) return X;
    else
    {
        HALF = N/2;
        if (2* HALF == N)
            return A5Q(X, HALF) * A5Q(X,HALF);
        else return A5Q(X, HALF) * A5Q(X,HALF) * X;
    }
}
