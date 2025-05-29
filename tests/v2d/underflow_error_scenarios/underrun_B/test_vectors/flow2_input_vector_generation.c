#include <stdio.h>
#define NUM_BLOCKS 1
#define INPUT_BLOCK_SIZE 8
#define VEC 32
int main (int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Should run the executable with below commands\n");
        printf ("./a.out <NUM_VECTORS_BLOCK>\n");
    }

    FILE *fp;
    int i ,j, offset = 0, blc_cnt, num_vectors;
    num_vectors = atoi(argv[1]);
    fp =  fopen ("flow2_input.txt", "w");
    for (blc_cnt = 0; blc_cnt < NUM_BLOCKS; blc_cnt++)
    {
        offset += 0X00110014;
        for (i = 0; i < INPUT_BLOCK_SIZE; i++)
        {
            for (j = 0; j < num_vectors; j++)
            {
                int temp = ((i * 2* VEC + (j*2)) << 16| ((i* VEC + (j*2))));
                temp = temp + offset;
                fprintf (fp,"%08x\n", temp);
            }
        }
    }
    fclose(fp);

}
