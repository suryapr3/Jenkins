#include <stdio.h>
#include "rtl_api.h"
#include <string.h>

extern "C" void * svGetScopeFromName( char const * name );
extern "C" void svSetScope( void * scope );
extern int presil_start( int argc, char *argv[]);
#define MAX_NUMBER_OF_ARGUMENTS 50
#define MAX_INPUT_STRING_SIZE 500

extern "C" void start_c_code(const char *arg){
  int read_val;
  int mem_rd_val[64];
  int mem_wr_val[64];
  int addr;
  int i;
  int c;
  char str[128], name[128] ;
  char *argv[MAX_NUMBER_OF_ARGUMENTS];
  char input_string[MAX_INPUT_STRING_SIZE];
  unsigned int argc = 0;
  char *pch;
  
  svSetScope(svGetScopeFromName("egc_verif_fw_utils_pkg"));
  write_info("C_TEST: Starting C code. arg=%s", arg);
  write_info("C_TEST: Waiting for 100 clocks");
  wait_clks(100);

  write_info("Extract input Arguements");
  if ( strlen ( arg ) > MAX_INPUT_STRING_SIZE )
  {
 	write_error ("Option input string exceeds size" );
        return;
  }
    
  // Scrub the input.
  strcpy ( input_string, arg );
  for(c=0; c < strlen(input_string); c++)  if (input_string[c] < ' ' || input_string[c] > 126 ) input_string[c] = ' ';
  pch = strtok ( input_string, " " );
  argv[0] = "start_c_code";
  argc = 1;
  while ( pch != NULL )
  {
      if ( argc == 50 )
      {
          write_error("Number of options exceed the limit" );
          //return ( 1 );
      }
      argv[argc] = pch;
      ++argc;
      pch = strtok ( NULL, " " );
  }
  for ( c = 0; c < argc; ++c )
  {
      write_info ( "%s", argv[c] );
  }

#ifdef BUILD_EXAMPLE_CODE
  write_info("C_TEST: Writing 0xabcd to ext_to_rcs_mb[0] address 0x0026c038");
  write_reg(0x0026c038, 0xabcd);
  write_info("C_TEST: Waiting for 100 ns");
  wait_ns(100);
  write_warning("C_TEST: test of warning function");
  write_info("C_TEST: Reading address 0");
  read_val = read_reg(0x0026c038 ) ;
  sprintf ( str, "Address 0x0026c038, saw 0x%0x", read_val ) ;
  if ( read_val == 0xabcd ) {
    write_info( str ) ;
  } else {
    write_error( str ) ;
  }

  sprintf ( name, "ext_to_rcs_mb[1]" ) ; // Put register name here

  write_info("C_TEST: Writing 0x9876 to %s", name);
  write_ral(name , 0x9876);
  read_val = read_ral( name ) ;
  sprintf ( str, "RAL %s, saw 0x%0x", name, read_val ) ;
  if ( read_val == 0x9876 ) {
    write_info( str ) ;
  } else {
    write_error( str ) ;
  }

  if ( 0 ) {
    write_error("C_TEST: test of error function");
  }
  mem_wr_val[0] = 0xdeadbeef;
  mem_wr_val[1] = 0xabcd1234;
  mem_wr_val[2] = 0xaaaa2222;
  addr = 0x4000;
  write_mem("RSM", addr, 3, mem_wr_val);
  write_info("C_TEST: Wrote 3 words of data to address starting at 0x40000");
  sprintf(str, "C_TEST: Current simulation time before wait_clks: %0d", get_curr_sim_time_in_ns());
  write_info(str);
  wait_clks(1000);
  sprintf(str, "C_TEST: Current simulation time after wait_clks: %0d", get_curr_sim_time_in_ns());
  write_info(str);
  for(i =0; i<3; i++) {
    read_mem( "RSM", addr, 1, mem_rd_val);
    sprintf(str, "C_TEST: Value read from memory at address %x: %x", addr, mem_rd_val[0]);
    if (mem_rd_val[0] == mem_wr_val[i]) {
        write_info(str);
    } else {
        write_error(str);
    }
    addr += 4;
  }
#endif

  presil_start( argc, argv );
  wait_ns(500);
  write_info("C_TEST: finishing.");
}
