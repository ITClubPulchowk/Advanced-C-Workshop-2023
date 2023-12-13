#include<stdio.h>

struct counters {
    // int little : 2;
    // int medium : 4;
    // int large  : 6;

    unsigned int little : 2;
    unsigned int medium : 4;
    unsigned int large  : 6;
};

#define NUM_LOOPS 50

int main()
{
    struct counters counts;
    counts.little = 0;
    counts.medium = 0;
    counts.large = 0;
    for(int i=0; i < NUM_LOOPS; i++) {
        counts.little++;
        counts.medium++;
        counts.large++;
        printf("%d\t%d\t%d\n", counts.little, counts.medium, counts.large);
    }
    return 0;
}