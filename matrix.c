#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    clock_t t;
    t = clock();
    int r1 = 1000, c1 = 1000, r2 = 1000, c2 = 1000, i, j, k;

    // Dynamic allocation.

    int(*a)[r1][c1] = malloc(sizeof *a);
    int(*b)[r2][c2] = malloc(sizeof *b);
    int(*result)[r1][c2] = malloc(sizeof *result);

    // Storing elements of first matrix.
   
    for (i = 0; i < r1; ++i)
    {
        for (j = 0; j < c1; ++j)
        {
            (*a)[i][j] = rand() % 20;
        }
    }

    // Storing elements of second matrix.
   

    for (i = 0; i < r2; ++i)
    {
        for (j = 0; j < c2; ++j)
        {
            (*b)[i][j] = rand() % 20;
        }
    }
    // Initializing all elements of result matrix to 0
    for (i = 0; i < r1; ++i)
    {
        for (j = 0; j < c2; ++j)
        {
            (*result)[i][j] = 0;
        }
    }
    // Multiplying matrices a and b and
    // storing result in result matrix
    for (i = 0; i < r1; ++i)
        for (j = 0; j < c2; ++j)
            for (k = 0; k < c1; ++k)
            {
                (*result)[i][j] += (*a)[i][k] * (*b)[k][j];
            }
    // Displaying the result
    printf("\nOutput Matrix:\n");
    for (i = 0; i < r1; ++i)
        for (j = 0; j < c2; ++j)
        {
            printf("%d  ", (*result)[i][j]);
            if (j == c2 - 1)
                printf("\n\n");
        }
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

   

    free(a);
    free(b);
    free(result);
    return 0;
}
