
#include "stdarg.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

// Functions from DPI export - need to be declared here with the same footprint
// See src/val/env/abc_soc/abc_soc_fw_funcs.sv

// namespace egc_verif_fw_utils {
extern "C" {
void SVTask_rand_int (int *rint);

void SVTask_wait_ns (int n);
void SVTask_wait_clks (int n);
void SVTask_get_sim_time_in_ns (int *simtime);

void SVTask_write_fatal (char const *str);
void SVTask_write_error (char const *str);
void SVTask_write_warning (char const *str);
void SVTask_write_info (char const *str);

void SVTask_write_reg_32b (int address, int data);
void SVTask_write_reg_array (int address, int len, int *data);

void SVTask_write_ral_32b (char const *name, int data);
void SVTask_write_ral_array (char const *name, int len, int *data);

void SVTask_read_reg_32b (int address, int *data);
void SVTask_read_reg_array (int address, int len, int *data);

void SVTask_read_ral_32b (char const *name, int *data);
void SVTask_read_ral_array (char const *name, int len, int *data);

void SVTask_read_mem_32b (char const *mem_name, int address, int rd_len, int *data);
void SVTask_write_mem_32b (char const *mem_name, int address, int wr_len, int *data);

void SVTask_do_cmd (char const *cmd, int *idata, int *odata);
};
//} ;

// function: reg_read
//
// Returns data from register address
//
int read_reg (int address)
{
    int data;

    SVTask_read_reg_32b (address, (int *)&data);
    return data;
}

//
// function: reg_write
//
// Writes data to register address
//

void write_reg (int address, int data)
{
    SVTask_write_reg_32b (address, data);
}

// function: reg_read_array
//
// Returns data from register address
//
void read_reg_array (int address, int len, int data[16])
{
    SVTask_read_reg_array (address, len, data);
}

//
// function: reg_write_array
//
// Writes data to register address
//

void write_reg_array (int address, int len, int data[16])
{
    SVTask_write_reg_array (address, len, data);
}

// function: ral_read
//
// Returns data from ral location
//
int read_ral (char const *name)
{
    int data;

    SVTask_read_ral_32b (name, (int *)&data);
    return data;
}

//
// function: ral_write
//
// Writes data to ral location
//

void write_ral (char const *name, int data)
{
    SVTask_write_ral_32b (name, data);
}

// function: ral_read_array
//
// Returns data from ral location
//
void read_ral_array (char const *name, int len, int data[16])
{
    SVTask_read_ral_array (name, len, data);
}

//
// function: ral_write_array
//
// Writes data to ral location
//

void write_ral_array (char const *name, int len, int data[16])
{
    SVTask_write_ral_array (name, len, data);
}

//
// function: rand_int
//
// Get random integer from verification
//

int get_rand_int ()
{
    int rint;
    SVTask_rand_int (&rint);
    return rint;
}

//
// function: wait_ns
//
// Hardware delay in terms of 1ns increments
//

void wait_ns (int n)
{
    SVTask_wait_ns (n);
}

//
// function: wait_clks
//
// Hardware delay in terms of number of SPI bus clock cycles
//

void wait_clks (int n)
{
    SVTask_wait_clks (n);
}

//
// function: write_mem
//
// Writes data memory at address
// wr_len: length of the write in 32-bit words
//

void write_mem (char const *mem_name, int address, int wr_len, int *p_input)
{
    int scratch[64];
    if (wr_len > 60)
    {
        int blocks = wr_len / 60;
        int remainder = wr_len % 60;
        for (int i = 0; i < blocks; ++i)
        {
            memcpy (scratch, &p_input[i * 60], sizeof (int) * 60);
            SVTask_write_mem_32b (mem_name, address, 60, scratch);
            address += (60 * 4);
        }
        memcpy (scratch, &p_input[blocks * 60], sizeof (int) * remainder);
        SVTask_write_mem_32b (mem_name, address, remainder, scratch);
    }
    else
    {
        memcpy (scratch, p_input, sizeof (int) * wr_len);
        SVTask_write_mem_32b (mem_name, address, wr_len, scratch);
    }

    // SVTask_write_mem_32b(mem_name, address, wr_len, data);
}

//
// function: read_mem
//
// Read data from memory at address
// rd_len: length of the the read in 32-bit words
//

void read_mem (char const *mem_name, int address, int rd_len, int *p_output)
{
    int scratch[64];
    if (rd_len > 60)
    {
        int blocks = rd_len / 60;
        int remainder = rd_len % 60;
        for (int i = 0; i < blocks; ++i)
        {
            SVTask_read_mem_32b (mem_name, address, 60, scratch);
            memcpy (&p_output[i * 60], scratch, sizeof (int) * 60);
            address += (60 * 4);
        }
        SVTask_read_mem_32b (mem_name, address, remainder, scratch);
        memcpy (&p_output[blocks * 60], scratch, sizeof (int) * remainder);
    }
    else
    {
        SVTask_read_mem_32b (mem_name, address, rd_len, scratch);
        memcpy (p_output, scratch, sizeof (int) * rd_len);
    }

    // VTask_read_mem_32b(mem_name, address, rd_len, data);
}

// function: get_curr_sim_time_in_ns
//
// Returns the current simulation time in ns

int get_curr_sim_time_in_ns ()
{
    int simtime;
    SVTask_get_sim_time_in_ns (&simtime);
    return simtime;
}

// function: do_cmd
//
// execute user command
//

void do_cmd (char const *cmd, int *idata, int *odata)
{
    SVTask_do_cmd (cmd, idata, odata);
}

// function: write_info
//
// Writes information to a file

void write_info (const char *fmt, ...)
{
    va_list args;
    char str[1000];
    va_start (args, fmt);
    vsnprintf (str, sizeof (str), fmt, args);
    va_end (args);
    SVTask_write_info (str);
}

// function: write_warning
//
// Writes warning to a file

void write_warning (const char *fmt, ...)
{
    va_list args;
    char str[1000];
    va_start (args, fmt);
    vsnprintf (str, sizeof (str), fmt, args);
    va_end (args);
    SVTask_write_warning (str);
}

// function: write_error
//
// Writes error to a file

void write_error (const char *fmt, ...)
{
    va_list args;
    char str[1000];
    va_start (args, fmt);
    vsnprintf (str, sizeof (str), fmt, args);
    va_end (args);
    SVTask_write_error (str);
}

// function: write_fatal
//
// Writes fatal to a file

void write_fatal (const char *fmt, ...)
{
    va_list args;
    char str[1000];
    va_start (args, fmt);
    vsnprintf (str, sizeof (str), fmt, args);
    va_end (args);
    SVTask_write_fatal (str);
}
