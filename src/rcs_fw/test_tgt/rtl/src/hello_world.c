
#include "cal_rtl_param.h"
#include "presil_msg_test.h"
#include "rtl_api.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" void trax_trace_file_gen (const char *trace_mem, const int trace_addr);

extern "C" void *svGetScopeFromName (char const *name);
extern "C" void svSetScope (void *scope);

/**
 * Example C code
 */

int presil_start (int argc, char *argv[])
{
    write_info ("Hello! let us build on this!");

    int c;
    int run_time = 50;
    bool wait_for_ready = true;

    while ((c = getopt (argc, argv, "r:wem")) != -1)
    {
        switch (c)
        {
            case 'r': run_time = atoi (optarg); break;
            case 'w': wait_for_ready = false; break;
            case 'e':
                write_info ("starting simple eigen test");
                wait_ns (220000);
                // Read back the result
                cal_eigentest_post_process ();
                write_info ("Cal EigenTest completed");
                break;
            case 'm':
                write_info ("Message Test");
                msg_handler_test ();
                break;
        }
    }

    // Wait for ALL cpus to boot.
    if (wait_for_ready)
    {
        int cpu0_idx = 8;
        int cpu1_idx = 10;
        int cpu2_idx = 12;
        int cpu0_status;
        int cpu1_status;
        int cpu2_status;
        int cpus_ready = 0;
        int mem_rd_val[64];
        int mem_wr_val[64];
        do
        {
            read_mem ("RSM", 0, 16, mem_rd_val);
            cpu0_status = mem_rd_val[cpu0_idx];
            cpu1_status = mem_rd_val[cpu1_idx];
            cpu2_status = mem_rd_val[cpu2_idx];

            write_info ("CPU0: %d   CPU1: %d    CPU2: %d", cpu0_status, cpu1_status, cpu2_status);
            if (cpu0_status == 3 && cpu1_status == 3 && cpu2_status == 3)
                cpus_ready = 1;
            wait_ns (500);

        } while (!cpus_ready);
    }

    // Run the test.
    wait_ns (run_time * 1000);

    // Determine if there is TRAX data, and save it.
    trax_trace_file_gen ("RSM", 0x10000);
    trax_trace_file_gen ("RSM", 0x10000 + 4 * (32 + 128));
    trax_trace_file_gen ("RSM", 0x10000 + 8 * (32 + 128));

    wait_ns (1000);

    return (0);
}
