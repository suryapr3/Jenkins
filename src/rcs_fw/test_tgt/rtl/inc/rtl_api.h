
#include "stdint.h"
#include "stdarg.h"

//} ;

// function: reg_read
//
// Returns data from register address
//
int read_reg(int address);

//
// function: reg_write
//
// Writes data to register address
//

void write_reg(int address, int data);

// function: reg_read_array
//
// Returns data from register address
//
void read_reg_array(int address, int len, int data[16] );

//
// function: reg_write_array
//
// Writes data to register address
//

void write_reg_array(int address, int len, int data[16]); 

// function: ral_read
//
// Returns data from ral location
//
int read_ral(char const * name );

//
// function: ral_write
//
// Writes data to ral location
//

void write_ral(char const * name, int data); 

// function: ral_read_array
//
// Returns data from ral location
//
void read_ral_array(char const * name, int len, int data[16] );

//
// function: ral_write_array
//
// Writes data to ral location
//

void write_ral_array(char const * name, int len, int data[16]);

//
// function: rand_int
//
// Get random integer from verification
//

int get_rand_int ();

//
// function: wait_ns
//
// Hardware delay in terms of 1ns increments
//

void wait_ns(int n);

//
// function: wait_clks
//
// Hardware delay in terms of number of SPI bus clock cycles
//

void wait_clks(int n);

//
// function: write_mem
//
// Writes data memory at address
// wr_len: length of the write in 32-bit words
//

void write_mem(char const * mem_name, int address, int wr_len, int *p_data);

//
// function: read_mem
//
// Read data from memory at address
// rd_len: length of the the read in 32-bit words
//

void read_mem(char const * mem_name, int address, int rd_len, int *p_data);

// function: get_curr_sim_time_in_ns
//
// Returns the current simulation time in ns

int get_curr_sim_time_in_ns();

// function: do_cmd
//
// execute user command
//

void do_cmd ( char const * cmd, int *idata, int *odata );

// function: write_info
//
// Writes information to a file

void write_info( const char * fmt, ... ); 

// function: write_warning
//
// Writes warning to a file

void write_warning( const char * fmt, ... ) ;

// function: write_error
//
// Writes error to a file

void write_error( const char * fmt, ... );

// function: write_fatal
//
// Writes fatal to a file

void write_fatal( const char * fmt, ... );
