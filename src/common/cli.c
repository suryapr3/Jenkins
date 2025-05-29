/**********************************************************************************************
* INTEL CONFIDENTIAL
* Copyright (C) 2022 Intel Corporation
* This software and the related documents ("Material") are Intel copyrighted materials,
* and your use of them is governed by the express license under which they were provided
* to you ("License"). Unless the License provides otherwise, you may not use, modify,
* copy, publish, distribute, disclose or transmit this software or the related documents
* without Intel's prior written permission.
* This software and the related documents are provided as is, with no express or implied
* warranties, other than those that are expressly stated in the License.
* No license under any patent, copyright, trade secret or other intellectual property
* right is granted to or conferred upon you by disclosure or delivery of the Materials,
* either expressly, by implication, inducement, estoppel or otherwise. Any license under
* such intellectual property rights must be expressed and approved by Intel in writing.
*********************************************************************************************/
/********************************************************************************************
 * @file    cli.c
*********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "com_definitions.h"
#include "all_comps.h"
#include "cli.h"
#include "init.h"
#include "logger.h"
#include "srp.h"
#include "srp_status.h"
#include "srp_block_ids.h"
#include "srp_rcs.h"
#include "srp_vex.h"

/******************************************************************************
*Function        : unsigned int hex2int
*Description     : The function hex2int converts a hexadecimal string to an unsigned integer
*@input paramter : char *hex
*@return         : val
*******************************************************************************/

unsigned int hex2int(char *hex)
{
    unsigned int val = 0;
    while (*hex)
    {
        char byte = *hex++;                                // get current character then increment
        if (byte >= '0' && byte <= '9') byte = byte - '0'; // transform hex character to the 4bit equivalent number, using the ascii table indexes

        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;
        val = (val << 4) | (byte & 0xF);                   // shift 4 to make space for new digit, and add the 4 bits of the new digit

    }
    return val;
}

/******************************************************************************
*Function        : unsigned int readReg
*Description     : The function reads the register value as hexadecimal
                   converts into unsigned integer using hex2int
*@input paramter : uint32_t addr
*@return         : data
*******************************************************************************/

unsigned int readReg(uint32_t addr)
{
      uint32_t data;
      FILE *fp;
      char command[50];
      char line[30];
      char seps[] = " ";
      char *portion1;
      char *portion2;
      snprintf(command,sizeof(command), "srpRead 0x%x", addr);
      fp = popen(command, "r");
      while (fgets(line, sizeof line, fp))
      {
          portion1 = strtok(line, seps);
          portion2 = strtok(NULL, seps);
      }
      pclose(fp);
      data = hex2int(portion2);
      return data;
}

/******************************************************************************
*Function        : unsigned int writeReg
*Description     : The function writes data into register, reads the value
                   through mask and writes the value to register
*@input paramter : uint32_t addr, uint32_t data,uint32_t mask
*******************************************************************************/

unsigned int writeReg(uint32_t addr, uint32_t data, uint32_t mask)
{
      uint32_t data_to_write;
      uint32_t present_data;
      present_data = readReg(addr);
      data_to_write = ((present_data & ~(mask)) | ( data & mask ));
      FILE *fp;
      char command[50];
      snprintf(command,sizeof(command), "srpWrite 0x%x 0x%x", addr, data_to_write);
      system(command);
      return 0;
}

/******************************************************************************
*Function        : unsigned int writeMem
*Description     : The function writes into memory using mask,
                   iterates over the array reads the value,
                   calculates new value using mask and write into memory
*@input paramter : uint32_t addr, uint32_t write_data_array,uint32_t mask,
                   uint32_t const size
*******************************************************************************/

unsigned int writeMem(uint32_t addr, uint32_t write_data_array[], uint32_t mask, uint32_t const size)
{
      uint32_t data_to_write;
      uint32_t present_data;
      char command[100];
      uint32_t count;
      for(count=0; count<size; count+=1)
      {
          present_data = readReg(addr + count*4);
          LOG_PRINT("present data after mask at index %d  and at address 0x%x is 0x%x\n",count, (addr + count*4), (present_data & ~(mask)));
          LOG_PRINT("data as input at index %d  and at address 0x%x is 0x%x\n",count, (addr + count*4), write_data_array[count]);
          data_to_write = ((present_data & ~(mask)) | ( write_data_array[count] & mask ));
          LOG_PRINT("data to write at index %d  and at address 0x%x is 0x%x\n",count, (addr + count*4), data_to_write);
          snprintf(command,sizeof(command), "srpWrite 0x%x 0x%x",addr + count*4, data_to_write);
          system(command);
      }
      return 0;
}

/******************************************************************************
*Function        : unsigned int readRegExpect
*Description     : The function reads the register value compares the data
                   with expected data using mask
*@input paramter : uint32_t addr, uint32_t expected_data,uint32_t mask
*@return         : return 0 if matches
                   return 1 if not
*******************************************************************************/

unsigned int readRegExpect(uint32_t addr, uint32_t expected_data, uint32_t mask)
{
      uint32_t data;
      FILE *fp;
      char command[50];
      char line[30];
      char seps[] = " ";
      char *portion1;
      char *portion2;
      snprintf(command,sizeof(command), "srpRead 0x%x", addr);
      fp = popen(command, "r");
      while (fgets(line, sizeof line, fp))
      {
          portion1 = strtok(line, seps);
          portion2 = strtok(NULL, seps);
      }
      pclose(fp);
      data = hex2int(portion2);
      if ((data & mask) == (expected_data & mask))
      {
         LOG_PRINT("read data is same as expected data\n");
         return 0;
      }
      else
      {
         LOG_PRINT("read data does not match expected data\n");
         LOG_PRINT("read data is 0x%x\n", data);
         LOG_PRINT("mask is 0x%x\n", mask);
         LOG_PRINT("expected data is 0x%x\n", expected_data);
         return 1;
      }
}

/******************************************************************************
*Function        : unsigned int readMem
*Description     : The function reads a memory stores data into array,
                   converts data from hexa to int and stores in array
*@input paramter : uint32_t addr, uint32_t size,uint32_t read_data_array
*******************************************************************************/

void readMem(uint32_t addr, uint32_t const size, uint32_t *read_data_array)
{
      uint32_t data;
      FILE *fp;
      char command[50];
      char line[30];
      char seps[] = " ";
      char *portion1;
      char *portion2;
      uint32_t count;
      for (count =0; count < size; count+= 1)
      {
          snprintf(command, sizeof(command), "srpRead 0x%x", (addr + count * 4));
          fp = popen(command, "r");
          while (fgets(line, sizeof line, fp))
          {
              portion1 = strtok(line, seps);
              portion2 = strtok(NULL, seps);
          }
         pclose(fp);
         data = hex2int(portion2);
         read_data_array[count] = data;
     }
      for(count=0;count <size;count+=1)
      {
         LOG_PRINT("for read data 0x%x count is %d\n", read_data_array[count], count);
      }
}

/******************************************************************************
*Function        : unsigned int vexStart
*Description     : The function starts VEX core at given address
                   by execution system command with provided core ID and start address
*@input paramter : uint32_t vex_core_id, uint32_t vex_start_address
*******************************************************************************/

uint32_t vexStart( uint32_t vex_core_id, uint32_t vex_start_address)
{
      char command[50];
      snprintf(command, sizeof(command), "srpVexStart -c 0x%x -a 0x%x", vex_core_id, vex_start_address);
      system(command);
      return 0;
}

/*********************************************************************
*Function         : read_reg64_18a
*Description      : This fucntion does the following
*                   1. reads the value of the 64 bit register
* @input parameter: uint32_t address
*                   char regname[]
* @return         : returns the 64 bit value read data
*********************************************************************/

uint64_t read_reg64_18a(uint32_t address, char regname[])
{
    uint32_t buffer_LSB;
    uint32_t buffer_MSB;
    uint64_t buffer;
    uint32_t flags =0;
    buffer_LSB = read_reg_18a(address, regname);
    buffer_MSB = read_reg_18a(address+0x4, regname);
    buffer = (uint64_t)buffer_MSB << 32 | buffer_LSB;
    LOG_INFO("data read operation from register %s at address 0x%x is successful and data read is 0x%x", regname, address, buffer);
    return buffer;
}

/*********************************************************************
*Function         : read_reg128_18a
*Description      : This fucntion does the following
*                   1. reads the value of the 128 bit register
* @input parameter: uint128_t address
*                   char regname[]
* @return         : returns the 128 bit value read data
*********************************************************************/

uint128_t read_reg128_18a(uint32_t address, char regname[])
{
    uint64_t buffer_LSB;
    uint64_t buffer_MSB;
    uint128_t buffer;
    uint32_t flags =0;
    buffer_LSB = read_reg64_18a(address, regname);
    buffer_MSB = read_reg64_18a(address+0x8, regname);
    buffer = (uint128_t)buffer_MSB << 64 | buffer_LSB;
    LOG_INFO("data read operation from register %s at address 0x%x is successful and data read is 0x%x", regname, address, buffer);
    return buffer;
}

/*********************************************************************
*Function         : read_reg_expect128_18a
*Description      : This fucntion does the following
*                     1. reads the initial value of the register
*                     2. reads back the register and ANDING the read data with the read mask
*                     3. compares the result of step 2 AND read mask with AND of expected data
* @input parameter: uint128_t address, uint128_t expected_data, uint128_t read_mask, char regname[]
* @return         : 0 => read is successful and read data matches with expected data
*                 : 1 => read is not successful or read data does not matches with expected data
*********************************************************************/

uint128_t read_reg_expect128_18a(uint32_t address, uint128_t expected_data, uint128_t read_mask, char regname[])
{
    uint128_t buffer;
    buffer = read_reg128_18a(address, regname);
    LOG_PRINT("buffer & read_mask is 0x%x", buffer & read_mask);
    LOG_PRINT("expected_data & read_mask is 0x%x", expected_data & read_mask);
    if ((buffer & read_mask) == (expected_data & read_mask))
    {
        LOG_INFO("data read from address [0x%x] is 0x%x and the expected data is 0x%x", address, buffer, expected_data);
        return 0;
    }
    else
    {
        LOG_ERROR("data read from register %s is different than expected", regname);
        LOG_INFO("data read from address [0x%x] is 0x%x, read_mask is 0x%x but the expected data is 0x%x\n", address, buffer, expected_data);
        return 1;
    }
}

/*********************************************************************
 *Function         : read_reg_18a
 *Description      : This fucntion does the following
 *                     1. reads the value of the register
 * @input parameter: uint32_t address
 *                   char regname[]
 * @return         : returns the 32 bit value read data
 *********************************************************************/

uint32_t read_reg_18a(uint32_t address, char regname[])
{
    uint32_t srp_read_status = 0;
    uint32_t buffer;
    uint32_t flags =0;
    srp_read_status = srp_dev_read32(srp, address, &buffer);
    if(srp_read_status != SRP_ST_SUCCESS)
         LOG_ERROR("data read operation from register %s at address 0x%x is not successful", regname, address);
    else
         LOG_INFO("data read operation from register %s at address 0x%x is successful and data read is 0x%x", regname, address, buffer);
    return buffer;
}

/*********************************************************************
 *Function         : read_mem_18a
 *Description      : This fucntion does the following
 *                     1. reads the content of the memory
 * @input parameter: uint64_t offset, uint32_t size, uint32_t * buffer,
 *                   char regname[]
 *********************************************************************/

void read_mem_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[])
{
    uint32_t srp_read_status = 0;
    uint32_t flags = 0;

    srp_read_status = srp_dev_buf_read32(srp, address, buffer, size, flags);
    if(srp_read_status != SRP_ST_SUCCESS)
        LOG_ERROR("data read operation from memory %s at address 0x%x for size %d is not successful", memname, address, size);
    else
        LOG_INFO("data read operation from memory %s at address 0x%x for size %d is successful", memname, address, size);
}

/*********************************************************************
 *Function         : write_mem_18a
 *Description      : This fucntion does the following
 *                     1. writes the content of the memory
 * @input parameter: uint32_t address, uint32_t size, uint32_t *buffer,
 *                   char regname[]
 *********************************************************************/

uint32_t write_mem_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[])
{
    uint32_t srp_write_status = 0;
    uint32_t flags = 0;

    srp_write_status = srp_dev_buf_write32(srp, address, buffer, size, flags);
    if(srp_write_status != SRP_ST_SUCCESS)
        LOG_ERROR("data write operation to memory %s at address 0x%x for size %d is not successful", memname, address, size);
    else
        LOG_INFO("data write operation to memory %s at address 0x%x for size %d is successful", memname, address, size);
    return 0;
}

/*********************************************************************
 *Function         : write_read_mem_expect_18a
 *Description      : This fucntion does the following
 *                     1. writes the content of the memory
 *                     2. reads the  contents of the memory
 *                     3. compares the read data with the write data
 *@input parameter: uint16_t block_id, uint16_t region_id, uint64_t offset
 *                   char regname[]
 *********************************************************************/

void write_read_mem_expect_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[])
{
    uint32_t srp_write_status = 0;
    uint32_t srp_read_status = 0;
    uint32_t flags = 0;
    uint32_t i=0;
    uint32_t read_buffer[size];
    srp_write_status = srp_dev_buf_write32(srp, address, buffer, size, flags);
    if(srp_write_status != SRP_ST_SUCCESS)
        LOG_ERROR("data write operation to memory %s at address 0x%x for size %d is not successful", memname, address, size);
    else
        LOG_INFO("data write operation to memory %s at address 0x%x for size %d is successful", memname, address, size);
    srp_read_status = srp_dev_buf_read32(srp, address, read_buffer, size, flags);
    if(srp_read_status != SRP_ST_SUCCESS)
        LOG_ERROR("data read operation from memory %s at address 0x%x for size %d is not successful", memname, address, size);
    else
        LOG_INFO("data read operation from memory %s at address 0x%x for size %d is successful", memname, address, size);
    for(i=0; i <size; i++)
    {
        if(buffer[i] != read_buffer[i])
        {
             LOG_ERROR("data read from memory %s at address [0x%x] ,read data= 0x%x and expected data= 0x%x", \
                       memname, address, read_buffer[i], buffer[i]);
        }
    }
}

/*********************************************************************
 *Function         : read_mem_expect_18a
 *Description      : This fucntion does the following
 *                     1. reads the  contents of the memory
 *                     2. compares the read data with the expected data
 *@input parameter: uint16_t block_id, uint16_t region_id, uint64_t offset
 *                   char regname[]
 * @output parameter: status
 *********************************************************************/

int read_mem_expect_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[])
{
    uint32_t srp_write_status = 0;
    uint32_t srp_read_status = 0;
    uint32_t flags = 0;
    uint32_t i=0;
    uint32_t read_buffer[size];
    int rv = 0;

    srp_read_status = srp_dev_buf_read32(srp, address, read_buffer, size, flags);

    if (srp_read_status != SRP_ST_SUCCESS)
        LOG_ERROR("data read operation from memory %s at address 0x%x for size %d is not successful", memname, address, size);
    else
        LOG_INFO("data read operation from memory %s at address 0x%x for size %d is successful", memname, address, size);

    for (i=0; i <size; i++)
    {
        if (buffer[i] != read_buffer[i])
        {
             LOG_ERROR("data read from memory %s at address [0x%x] ,read data= 0x%x and expected data= 0x%x", \
                       memname, address, read_buffer[i], buffer[i]);
             rv |= 1;
        }
    }
    return rv;
}

/*********************************************************************
 *Function         : write_read_vex_pmem_expect_18a
 *Description      : This fucntion does the following
 *                     1. writes the content of the memory
 *                     2. reads the  contents of the memory
 *                     3. compares the read data with the write data
 *                     4. vex_pmem has some memory, which returns always0,
 *                     taking care of those memory locations, while comparing
 *                     the read data and expected data
 *@input parameter: uint16_t block_id, uint16_t region_id, uint64_t offset
 *                   char regname[]
 *********************************************************************/

void write_read_vex_pmem_expect_18a(uint32_t address, uint32_t size, uint32_t * buffer, char memname[])
{
    uint32_t srp_write_status = 0;
    uint32_t srp_read_status = 0;
    uint32_t flags = 0;
    uint32_t i=0;
    uint32_t read_buffer[size];

    srp_write_status = srp_dev_buf_write32(srp, address, buffer, size, flags);
    if(srp_write_status != SRP_ST_SUCCESS)
        LOG_ERROR("data write operation to memory %s at addrss 0x%x for size %d is not successful", memname, address, size);
    LOG_INFO("data write operation to memory %s at address 0x%x for size %d is successful", memname, address, size);
    srp_read_status = srp_dev_buf_read32(srp, address, read_buffer, size, flags);
    if(srp_read_status != SRP_ST_SUCCESS)
        LOG_ERROR("data read operation from memory %s at address 0x%x for size %d is not successful", memname, address, size);
    LOG_INFO("data read operation from memory %s at address 0x%x for size %d is successful", memname, address, size );
    for(i=0; i <size; i++)
    {
        if(buffer[i] != read_buffer[i])
        {
            LOG_ERROR("data read from memory %s at address [0x%x]  does not match, read data= 0x%x and expected data= 0x%x", \
                      memname, address,i*4, read_buffer[i], buffer[i]);
        }

    }
}

/*********************************************************************
*Function         : write_reg64_18a
*Description      : This fucntion write the data to the address with correct write address,
* @input parameter: uint32_t address
*                   uint32_t write_value, uint32_t write_mask, char regname[]
* @return         : 0 => read/write is successful
*                 : 1 => either read or write is not successful
*********************************************************************/

uint32_t write_reg64_18a(uint32_t address, uint64_t write_value, uint64_t write_mask, char regname[])
{
    uint32_t srp_write_status_LSB = 0;
    uint32_t srp_write_status_MSB = 0;
    uint32_t write_value_LSB;
    uint32_t write_value_MSB;
    uint32_t write_mask_LSB;
    uint32_t write_mask_MSB;

    write_value_LSB = write_value & 0xFFFFFFFF;
    write_value_MSB = (write_value >> 32) & 0xFFFFFFFF ;

    write_mask_LSB = write_mask;
    write_mask_MSB = write_mask >> 32 ;

    LOG_PRINT("write_value_LSB=%lx , write_value_MSB=%lx , address= %lx\n", write_value_LSB,write_value_MSB, address);
    srp_write_status_LSB = write_reg_18a(address, write_value_LSB, write_mask_LSB, regname);
    srp_write_status_MSB = write_reg_18a(address+0x4, write_value_MSB, write_mask_MSB, regname);
    LOG_PRINT("srp_write_status_LSB=%lx,srp_statlus_MSB=%lx\n", srp_write_status_LSB, srp_write_status_MSB);
    if(srp_write_status_LSB != SRP_ST_SUCCESS || srp_write_status_MSB != SRP_ST_SUCCESS)
        LOG_ERROR("data write operation from register %s  at address 0x%x is not successful", regname, address );
    else
        LOG_INFO("data write operation from register %s at address 0x%x is successful", regname, address );
    return (srp_write_status_LSB & srp_write_status_MSB);
}

/*********************************************************************
*Function         : write_reg128_18a
*Description      : This fucntion write the data to the address with correct write address,
* @input parameter: uint32_t address
*                   uint32_t write_value, uint32_t write_mask, char regname[]
* @return         : 0 => read/write is successful
*                 : 1 => either read or write is not successful
*********************************************************************/

uint64_t write_reg128_18a(uint32_t address, uint128_t write_value, uint128_t write_mask, char regname[])
{
    uint64_t srp_write_status_LSB = 0;
    uint64_t srp_write_status_MSB = 0;
    uint64_t write_value_LSB;
    uint64_t write_value_MSB;
    uint64_t write_mask_LSB;
    uint64_t write_mask_MSB;
    write_value_LSB = write_value & 0xFFFFFFFF;
    write_value_MSB = (write_value >>64)& 0xFFFFFFFF;
    write_mask_LSB = write_mask;
    write_mask_MSB = write_mask >> 64;

    LOG_PRINT("write_value_LSB=%lx , write_value_MSB=%lx , address= %lx\n", write_value_LSB, write_value_MSB, address);
    srp_write_status_LSB = write_reg64_18a(address, write_value_LSB, write_mask_LSB, regname);
    srp_write_status_MSB = write_reg64_18a(address+0x8, write_value_MSB, write_mask_MSB, regname);
    LOG_PRINT("srp_write_status_LSB=%lx,srp_write_status_MSB=%lx\n", srp_write_status_LSB, srp_write_status_MSB);
    if(srp_write_status_LSB != SRP_ST_SUCCESS || srp_write_status_MSB != SRP_ST_SUCCESS)
        LOG_ERROR("data write operation from register %s  at address 0x%x is not successful", regname, address );
    else
        LOG_INFO("data write operation from register %s at address 0x%x is successful", regname, address );
    return (srp_write_status_LSB & srp_write_status_MSB);
}

/*********************************************************************
*Function         : write_read_expect128_18a
*Description      : This fucntion does the following
*                     1. reads the initial value of the register
*                     2. reads back the register and ANDING the read data with the read mask
*                     3. compares the result of step 2 AND read mask with AND of expected data
* @input parameter: uint128_t address, uint128_t expected_data, uint128_t read_mask, char regname[]
* @return         : 0 => read is successful and read data matches with expected data
*                 : 1 => read is not successful or read data does not matches with expected data
*********************************************************************/

uint32_t write_read_expect128_18a(uint32_t address, uint128_t default_value, uint128_t write_value, \
                                  uint128_t expected_data, uint128_t read_mask, uint128_t write_mask, char regname[])
{
   uint32_t srp_write_status = 0;
   uint128_t buffer;
   uint32_t write_status=0;
   write_status = write_value & write_mask;

   srp_write_status = write_reg128_18a(address, write_value, write_mask, regname);
   if(srp_write_status != SRP_ST_SUCCESS)
    return 1;

   buffer = read_reg128_18a(address, regname);

   if ((buffer & read_mask) == (((expected_data & write_mask) & read_mask)) || (~ write_mask & default_value))
   {
        LOG_INFO("data read from register %s is same", regname);
        return 0;
   }
   else if(write_status==0)
   {
        LOG_INFO("The read value is 0x%x at address [0x%x], and the register %s is read only\n", buffer, address, regname);
        return 0;
   }

   else
   {
        LOG_ERROR("data read from register %s at address [0x%x] is unexpected, read_mask is 0x%x, \
                  write_mask is 0x%x,read data= 0x%x and expected data= 0x%x", \
                  regname, address, read_mask, write_mask, buffer, expected_data);
        return 1;
   }
}

/*********************************************************************
 *Function         : write_reg_18a
 *Description      : This fucntion write the data to the address with correct write address,
 * @input parameter: uint32_t address
 *                   uint32_t write_value, uint32_t write_mask, char regname[]
 * @return         : 0 => read/write is successful
 *                 : 1 => either read or write is not successful
 *********************************************************************/

uint32_t write_reg_18a(uint32_t address, uint32_t write_value,uint32_t write_mask, char regname[])
{
    uint32_t srp_write_status = 0;
    write_value &= write_mask;
    uint32_t flags =0;

    srp_write_status = srp_dev_write32(srp, address, write_value);
    if(srp_write_status != SRP_ST_SUCCESS)
        LOG_ERROR("data write operation from register %s  at address 0x%x is not successful", regname, address);
    else
        LOG_INFO("data write operation from register %s at address 0x%x is successful", regname, address);

    return srp_write_status;
}

/*********************************************************************
 *Function         : write_read_expect_18a
 *Description      : This fucntion does the following
 *                     1. reads the initial value of the register
 *                     2. reads back the register and ANDING the read data with the read mask
 *                     3. compares the result of step 2 AND read mask with AND of expected data
 * @input parameter: uint32_t address, uint32_t expected_data, uint32_t read_mask, char regname[]
 * @return         : 0 => read is successful and read data matches with expected data
 *                 : 1 => read is not successful or read data does not matches with expected data
 *********************************************************************/

uint32_t write_read_expect_18a(uint32_t address,uint32_t default_value, uint32_t write_value, \
                               uint32_t expected_data, uint32_t read_mask,uint32_t write_mask, char regname[])
{
    uint32_t srp_write_status = 0;
    uint32_t buffer,init_value;
    uint32_t write_status;
    write_status = write_value & write_mask;
    srp_write_status = write_reg_18a(address, write_value, write_mask, regname);
    if(srp_write_status != SRP_ST_SUCCESS)
        return 1;
    buffer = read_reg_18a(address, regname);

    if (((buffer & read_mask) == (((expected_data & write_mask) & read_mask))) || (~ write_mask & default_value))
    {
        LOG_INFO("data read from register %s is same", regname);
        return 0;
    }
    else if (write_status == 0)
    {
            LOG_INFO("data read from register %s is 0x%x and is read only\n", regname, buffer);
            return 0;
    }

    else
    {
        LOG_ERROR("data read from register %s at address [0x%x] is unexpected, read data= 0x%x and expected data= 0x%x, initial register value= 0x%x", \
        regname, address, buffer, expected_data, init_value);
        return 1;
    }
}

/*********************************************************************
 *Function         : read_reg_expect_18a
 *Description      : This fucntion does the following
 *                     1. reads the initial value of the register
 *                     2. reads back the register and ANDING the read data with the read mask
 *                     3. compares the result of step 2 AND read mask with AND of expected data
 * @input parameter: uint32_t address, uint32_t expected_data, uint32_t read_mask, char regname[]
 * @return         : 0 => read is successful and read data matches with expected data
 *                 : 1 => read is not successful or read data does not matches with expected data
 *********************************************************************/

uint32_t read_reg_expect_18a(uint32_t address,uint32_t expected_data, uint32_t read_mask, char regname[])
{
    uint32_t buffer;

    buffer = read_reg_18a(address, regname);
    if ((buffer & read_mask) == (expected_data & read_mask))
    {
        LOG_INFO("data read from address [0x%x] is 0x%x but the expected data is 0x%x\n", address, buffer, expected_data);
        return 0;
    }
    else
    {
        LOG_ERROR("data read from register %s is different than expected\n", regname);
        LOG_INFO("data read from address [0x%x] is 0x%x but the expected data is 0x%x\n", address, buffer, expected_data);
        return 1;
    }
}

void fill_random_buffer(uint32_t array[], uint32_t length)
{
    uint32_t i=0;
    srand(time(NULL));
    for(i=0; i<length; i++)
    {
        array[i] = rand();
    }
}
void fill_buffer(uint32_t array[], uint32_t length, uint32_t data)
{
    uint32_t i=0;
    for(i=0; i<length; i++)
    {
        array[i] = data;
    }
}
void fill_incrementing_buffer(uint32_t array[], uint32_t length, uint32_t data)
{
    uint32_t i=0;
    for(i=0; i<length; i++)
    {
        array[i] = data+i;
    }
}
void print_buffer (uint32_t array[],uint32_t length)
{
    uint32_t i= 0;
    for(i=0; i<length; i++)
    {
        LOG_INFO("data in array %d is 0x%x", i, array[i]);
    }
}
