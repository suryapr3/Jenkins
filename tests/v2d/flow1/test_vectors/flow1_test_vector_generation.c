#include <stdio.h>
#define NUM_OF_ELEMENTS_PER_VEC 32

int main(int argc, char **argv)
{
    FILE *fp = NULL;
    if (3 != argc)
    {
        printf("Not valid number of arguments\n");
        printf("./a.out <num_blocks> <number_of_vectors_block>");
    }
    int add_val = 0, i, j, k;
    fp = fopen("flow1_input.txt", "w");
    for (i = 0; i < atoi(argv[1]); i++)
    {
        for (j = 0; j < atoi(argv[2]); j++)
        {
            for (k = 0; k < NUM_OF_ELEMENTS_PER_VEC; k++)
            {
                fprintf (fp, "%08X\n", (((j* NUM_OF_ELEMENTS_PER_VEC + k) << 16) | (j * NUM_OF_ELEMENTS_PER_VEC + k)) + add_val);
            }
        }
        fprintf (fp, "%d Block completed\n", i+1);
        add_val++;
    }
}
