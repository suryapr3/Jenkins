#ifndef CLI_H
#define CLI_H
#ifndef UINT128_T_DEFINED
#define UINT128_T_DEFINED

typedef unsigned __int128 uint128_t;

#endif

extern void * srp;

unsigned int hex2int(char *hex);

uint32_t readReg(uint32_t addr);

uint32_t readRegExpect(uint32_t addr, uint32_t expected_data, uint32_t mask);

uint32_t writeReg(uint32_t addr,uint32_t data, uint32_t mask);

void readMem(uint32_t addr,uint32_t const size, uint32_t *read_data_array);

unsigned int writeMem(uint32_t addr,uint32_t *write_data_array, uint32_t mask,uint32_t const size);

uint32_t vexStart( uint32_t vex_core_id, uint32_t vex_start_address);

uint32_t read_reg(uint16_t block_id, uint16_t region_id, uint64_t offset, char regname[]);
uint32_t write_reg(uint16_t block_id, uint16_t region_id, uint64_t offset, uint32_t write_value,uint32_t write_mask, char regname[]);
uint32_t write_whole_reg(uint16_t block_id, uint16_t region_id, uint64_t offset, uint32_t write_value,uint32_t write_mask, char regname[]);
uint32_t read_reg_expect(uint16_t block_id, uint16_t region_id, uint64_t offset,uint32_t expected_data,uint32_t read_mask, char regname[]);
uint32_t read_write_expect(uint16_t block_id, uint16_t region_id, uint64_t offset,uint32_t write_data, uint32_t expected_data,uint32_t read_mask,uint32_t write_mask, char regname[]);
//uint32_t write_read_expect(uint16_t block_id, uint16_t region_id, uint64_t offset, uint32_t expected_data,uint32_t read_mask,uint32_t write_mask, char regname[]);
//uint32_t write_read_expect(uint16_t block_id, uint16_t region_id, uint64_t offset, uint32_t default_value, uint32_t write_value, uint32_t expected_data, uint32_t read_mask,uint32_t write_mask, char regname[])
uint32_t write_read_expect_18a(uint32_t address, uint32_t default_value, uint32_t write_value, uint32_t expected_data, uint32_t read_mask,uint32_t write_mask, char regname[]); 
void read_mem(uint16_t block_id, uint16_t region_id, uint64_t offset, uint32_t size, uint32_t * buffer, char memname[]);
void write_read_mem_expect(uint16_t block_id, uint16_t region_id, uint64_t offset, uint32_t size, uint32_t * buffer, char memname[]);
void write_read_mem_expect_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[]);
int read_mem_expect_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[]);
void write_read_vex_pmem_expect(uint16_t block_id, uint16_t region_id, uint64_t offset, uint32_t size, uint32_t * buffer, char memname[]);
void write_read_vex_pmem_expect_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[]);
void fill_random_buffer(uint32_t array[],uint32_t length);
void fill_buffer(uint32_t array[],uint32_t length,uint32_t data);
void fill_incrementing_buffer(uint32_t array[],uint32_t length, uint32_t data);
void print_buffer (uint32_t array[],uint32_t length);
uint32_t read_reg_18a(uint32_t address, char regname[]);
uint64_t read_reg64_18a(uint32_t address, char regname[]);
uint32_t read_reg_expect_18a(uint32_t address,uint32_t expected_data, uint32_t read_mask, char regname[]);
uint32_t write_reg_18a(uint32_t address, uint32_t write_value,uint32_t write_mask, char regname[]);
uint32_t write_reg64_18a(uint32_t address, uint64_t write_value, uint64_t write_mask, char regname[]);
void read_mem_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[]);
uint32_t write_mem_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[]);
uint32_t get_base_address(uint16_t block_id, uint16_t region_id);


uint128_t read_reg128_18a(uint32_t address, char regname[]);
uint128_t read_reg_expect128_18a(uint32_t address, uint128_t expected_data, uint128_t read_mask, char regname[]);
uint32_t write_read_expect128_18a(uint32_t address,uint128_t default_value, uint128_t write_value, uint128_t expected_data, uint128_t read_mask,uint128_t write_mask, char regname[]);
uint64_t write_reg128_18a(uint32_t address, uint128_t write_value,uint128_t write_mask, char regname[]);


#endif // CLI_H
