#include <stdio.h>
#define INPUT_BLOCK_SIZE 8
#define NUM_BLOCKS 1000
#define NUM_OF_ELEMENTS_PER_VEC 32

int main()
{
    FILE *fp = NULL, *fp_in = NULL;
    int add_val = 0x00020004, i, j, k, count = 0, add_temp = 0;
    int ref_input[INPUT_BLOCK_SIZE * NUM_OF_ELEMENTS_PER_VEC] = {0};
    fp = fopen("flow7_input_p5gsps_ref.txt", "w");
    fp_in = fopen("ref_output_p5gsps.txt","r");
    add_temp = 0;
    if (fp_in == NULL)
    {
        printf("file not presen\n");
        return;
    }

    for (i = 0; i < (INPUT_BLOCK_SIZE * NUM_OF_ELEMENTS_PER_VEC); i++)
    {
        int val = 0, rv = 0;
        rv = fscanf(fp_in, "%x", &val);
        if (rv != 1)
        {
            printf("ERROR %d\n", i);
            return -1;
        }
        ref_input[i] = val;
    }

    for (i = 0; i < NUM_BLOCKS; i++)
    {
        int elem_cnt = 0;
        for (j = 0; j < INPUT_BLOCK_SIZE; j++)
        {
            for (k = 0; k < NUM_OF_ELEMENTS_PER_VEC; k++)
            {
                int val = ref_input[elem_cnt];
                //fprintf (fp, "%08X - %08x\n", (((j* NUM_OF_ELEMENTS_PER_VEC + k) << 16) | (j * NUM_OF_ELEMENTS_PER_VEC + k)) + add_val, count);
                fprintf (fp, "%08x\n", val + add_temp);
                elem_cnt++;
            }
            count ++;
            //fprintf (fp, "\n");
        }
        //fprintf (fp, "%d Block completed\n", i+2);
        add_temp += add_val;
    }
}
