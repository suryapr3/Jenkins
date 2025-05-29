
#include <stdio.h>
#include <string.h>
#include "rtl_api.h"

#define TRACE_SIG 0xDDDA0000
#define TRACE_SIG_MASK 0xFFFFFF0F
#define TRACE_CORE(header)  ((header & 0x000000F0) >> 4)

#define TRACE_FMT_REGS_OFFSET       1
#define TRACE_FMT_DATA_OFFSET      32
#define TRACE_FMT_HEADER_WORDS     32

#define TRACE_FMT_TRAX_REGS_WORDS   32
#define TRACE_FMT_TRAX_DATA_WORDS  128
#define TRACE_DATA_READ_SIZE        32


extern "C" void trax_trace_file_gen( const char * trace_mem, const int trace_addr );

void trax_trace_file_gen( const char * trace_mem, const int trace_addr )
{

    int temp_buffer[64];

    read_mem( trace_mem, trace_addr, TRACE_FMT_HEADER_WORDS, temp_buffer );
    const int header_word = temp_buffer[0];

    if ( TRACE_SIG != (header_word & TRACE_SIG_MASK))
    {
        write_info( "No TRAX trace found at %s:%x", trace_mem, trace_addr );
        return;
    }

    uint32_t cpu = TRACE_CORE(header_word);

    char filename[32];
    sprintf( filename, "trax_cpu%d.dat", cpu );
    FILE *fout = fopen( filename, "w");

    if ( fout == NULL )
    {
        write_error( "Unable to open file for TRAX data: %s", filename );
        return;
    }

    write_info( "Opened file for TRAX data: %s", filename );

    uint32_t header_buffer[32];
    memset( header_buffer, 0, 128 );

    header_buffer[0] = 0x58415254; // "TRAXdmp"
    header_buffer[1] = 0x00706d64;
    header_buffer[2] = 0x00000100; // Version = 1
    header_buffer[3] = 0x00000300; // File size 768 bytes.
    header_buffer[4] = 0x00000100; // Trace offset 256 bytes.
    header_buffer[5] = 0x00000200; // Trace size 512 bytes.
                                   // dump time
                                   // flags
                                   // user name (16 bytes)
                                   // tool name (24 bytes)

    fwrite( header_buffer, 4, 32, fout );   // 32 words of header buffer.
    temp_buffer[TRACE_FMT_TRAX_REGS_WORDS] = 0;
    fwrite( &temp_buffer[TRACE_FMT_REGS_OFFSET], 4, TRACE_FMT_TRAX_REGS_WORDS, fout);         // 32 words of TRAX registers (last one zeroed).

    // Trax DATA:
    int data_words_read = 0;
    while (data_words_read < TRACE_FMT_TRAX_DATA_WORDS)
    {
        int address_offset = (data_words_read + TRACE_FMT_DATA_OFFSET) * 4;
        read_mem( trace_mem, trace_addr + address_offset,TRACE_DATA_READ_SIZE, temp_buffer );
        data_words_read += TRACE_DATA_READ_SIZE;

        fwrite( temp_buffer, 4, TRACE_DATA_READ_SIZE, fout);
    }

    fclose( fout );
}
