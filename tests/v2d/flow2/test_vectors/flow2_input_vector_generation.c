#include <stdio.h>
#define NUM_BLOCKS 1
#define INPUT_BLOCK_SIZE 8
#define VEC 32
int main (int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Should run the executable with below commands\n");
        printf ("./a.out <NUM_VECTORS_BLOCK>, <NUM_BLOCKS>\n");
    }

    FILE *fp;
    int i ,j, offset = 0, blc_cnt, num_vectors, num_blocks;
    num_vectors = atoi(argv[1]);
    num_blocks = atoi(argv[2]);
    fp =  fopen ("flow2_input.txt", "w");
    for (blc_cnt = 0; blc_cnt < num_blocks; blc_cnt++)
    {
        //offset += 0X00120014;
        offset += 0X0;
        for (i = 0; i < num_vectors; i++)
        {
            for (j = 0; j < VEC; j++)
            {
                int temp = ((i * 2* VEC + (j*2)) << 16| ((i* VEC + (j*2))));
                temp = temp + offset;
                fprintf (fp,"%08x\n", temp);
            }
        }
    }
    fclose(fp);

}
