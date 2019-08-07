#include <stdio.h>
#include <stdlib.h>

void tower_of_hanoi(int n, int fromPeg, int auxPeg, int toPeg)
{
    if(n == 1) printf("Move top disk from peg %d to peg %d\n", fromPeg, toPeg);
    else{
        tower_of_hanoi(n-1, fromPeg, toPeg, auxPeg);
        printf("Move top disk from peg %d to peg %d\n", fromPeg, toPeg);
        tower_of_hanoi(n-1, auxPeg, fromPeg, toPeg);
    }
}

int main()
{
    tower_of_hanoi(3, 1, 2, 3);
}
