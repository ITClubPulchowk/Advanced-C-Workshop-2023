#include <stdio.h>

int no_range(int a,int b)
{
    static int i =0;
    if(i==0)
    i=a;
    
    i++;
    return i;
}

int range(int a, int b)
{
    static long long int i;
    static int state = 0;
    switch (state)
    {
    case 0: /* start of function */
        state = 1;
        for (i = a; i < b; i++)
        {
            return i;
        /* Returns control to main */
        case 1:; /* resume control straight
                    after the return */
            printf("Control at range\n");
        }
    }
    state = 0;
    return 0;
}

// Driver code
int main()
{
    int i; // For really large numbers

    for (; i = range(1, 5);)
        printf("control at main :%d\n", i);

    return 0;
}
