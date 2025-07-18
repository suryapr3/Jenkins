#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include "cli.h"
#include "init.h"
#include "logger.h"
#include "srp.h"
#include "srpCliCommon.h"
#include "srp_block_ids.h"
#include "srp_core.h"
#include "srp_core_uapi.h"
#include "srp_rcs.h"
#include "srp_vex.h"
#include "all_comps.h"


int main(int argc, char **argv)
{
uint32_t read_value;
extern void * srp;
uint16_t i;
uint32_t error = 0;
uint32_t write_status = 0;
init();
for(i=0; i< 3;i++) {
   read_reg_expect(SRP_BLOCK_VHA ,i ,VHA_SCRATCH_OFFSET,VHA_SCRATCH_DEFAULT,VHA_SCRATCH_RD_MASK, "SRP_BLOCK_VEX_CORE.SCRATCH");
   read_reg_expect(SRP_BLOCK_VHA ,i ,VHA_CTL_OFFSET,VHA_CTL_DEFAULT,VHA_CTL_RD_MASK, "SRP_BLOCK_VEX_CORE.SCRATCH");
}
for(i=0;i<1;i++){
read_write_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_CONTROL_OFFSET,0xa5a5a5a5, 0xa5a5a5a5,VE32_CELL_MEM_CONTROL_RD_MASK,VE32_CELL_MEM_CONTROL_WR_MASK, "SRP_BLOCK_VEX_CORE.CONTROL");
}
for(i=0;i<18;i++){
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_CONTROL_OFFSET,VE32_CELL_MEM_CONTROL_DEFAULT,VE32_CELL_MEM_CONTROL_RD_MASK,"SRP_BLOCK_VEX_CORE.CONTROL");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_START_ADDR_OFFSET,VE32_CELL_MEM_START_ADDR_DEFAULT,VE32_CELL_MEM_START_ADDR_RD_MASK,"SRP_BLOCK_VEX_CORE.START_ADDR");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_STATUS_OFFSET,VE32_CELL_MEM_STATUS_DEFAULT,VE32_CELL_MEM_STATUS_RD_MASK,"SRP_BLOCK_VEX_CORE.STATUS");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_CELL_ID_OFFSET,VE32_CELL_MEM_CELL_ID_DEFAULT,VE32_CELL_MEM_CELL_ID_RD_MASK,"SRP_BLOCK_VEX_CORE.CELL_ID");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_COUNT_EXE_LSBS_OFFSET,VE32_CELL_MEM_COUNT_EXE_LSBS_DEFAULT,VE32_CELL_MEM_COUNT_EXE_LSBS_RD_MASK,"SRP_BLOCK_VEX_CORE.COUNT_EXE_LSBS");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_COUNT_EXE_MSBS_OFFSET,VE32_CELL_MEM_COUNT_EXE_MSBS_DEFAULT,VE32_CELL_MEM_COUNT_EXE_MSBS_RD_MASK,"SRP_BLOCK_VEX_CORE.COUNT_EXE_MSBS");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_COUNT_SLP_LSBS_OFFSET,VE32_CELL_MEM_COUNT_SLP_LSBS_DEFAULT,VE32_CELL_MEM_COUNT_SLP_LSBS_RD_MASK,"SRP_BLOCK_VEX_CORE.COUNT_SLP_LSBS");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_COUNT_SLP_MSBS_OFFSET,VE32_CELL_MEM_COUNT_SLP_MSBS_DEFAULT,VE32_CELL_MEM_COUNT_SLP_MSBS_RD_MASK,"SRP_BLOCK_VEX_CORE.COUNT_SLP_MSBS");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_COUNT_CLK_LSBS_OFFSET,VE32_CELL_MEM_COUNT_CLK_LSBS_DEFAULT,VE32_CELL_MEM_COUNT_CLK_LSBS_RD_MASK,"SRP_BLOCK_VEX_CORE.COUNT_CLK_LSBS");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_COUNT_CLK_MSBS_OFFSET,VE32_CELL_MEM_COUNT_CLK_MSBS_DEFAULT,VE32_CELL_MEM_COUNT_CLK_MSBS_RD_MASK,"SRP_BLOCK_VEX_CORE.COUNT_CLK_MSBS");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_ECC_IRQ_SBE_OFFSET,VE32_CELL_MEM_ECC_IRQ_SBE_DEFAULT,VE32_CELL_MEM_ECC_IRQ_SBE_RD_MASK,"SRP_BLOCK_VEX_CORE.ECC_IRQ_SBE");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_ECC_IRQ_DBE_OFFSET,VE32_CELL_MEM_ECC_IRQ_DBE_DEFAULT,VE32_CELL_MEM_ECC_IRQ_DBE_RD_MASK,"SRP_BLOCK_VEX_CORE.ECC_IRQ_DBE");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_ECC_IRQCLR_SBE_OFFSET,VE32_CELL_MEM_ECC_IRQCLR_SBE_DEFAULT,VE32_CELL_MEM_ECC_IRQCLR_SBE_RD_MASK,"SRP_BLOCK_VEX_CORE.ECC_IRQCLR_SBE");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_ECC_IRQCLR_DBE_OFFSET,VE32_CELL_MEM_ECC_IRQCLR_DBE_DEFAULT,VE32_CELL_MEM_ECC_IRQCLR_DBE_RD_MASK,"SRP_BLOCK_VEX_CORE.ECC_IRQCLR_DBE");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_SEQUENCER_IRQ_STTR_OFFSET,VE32_CELL_MEM_SEQUENCER_IRQ_STTR_DEFAULT,VE32_CELL_MEM_SEQUENCER_IRQ_STTR_RD_MASK,"SRP_BLOCK_VEX_CORE.SEQUENCER_IRQ_STTR");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_PMEM_SLAVE_ACCESS_OFFSET,VE32_CELL_MEM_PMEM_SLAVE_ACCESS_DEFAULT,VE32_CELL_MEM_PMEM_SLAVE_ACCESS_RD_MASK,"SRP_BLOCK_VEX_CORE.PMEM_SLAVE_ACCESS");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_IRQPRIO_STTR_IDLE_OFFSET,VE32_CELL_MEM_IRQPRIO_STTR_IDLE_DEFAULT,VE32_CELL_MEM_IRQPRIO_STTR_IDLE_RD_MASK,"SRP_BLOCK_VEX_CORE.IRQPRIO_STTR_IDLE");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_IRQPRIO_STTR_SLEEP_OFFSET,VE32_CELL_MEM_IRQPRIO_STTR_SLEEP_DEFAULT,VE32_CELL_MEM_IRQPRIO_STTR_SLEEP_RD_MASK,"SRP_BLOCK_VEX_CORE.IRQPRIO_STTR_SLEEP");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_BP_DMEM_ARB_DMEM_REQ_OFFSET,VE32_CELL_MEM_BP_DMEM_ARB_DMEM_REQ_DEFAULT,VE32_CELL_MEM_BP_DMEM_ARB_DMEM_REQ_RD_MASK,"SRP_BLOCK_VEX_CORE.BP_DMEM_ARB_DMEM_REQ");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_SIMD0_VMEM_ARB_VMEM_WP_OFFSET,VE32_CELL_MEM_SIMD0_VMEM_ARB_VMEM_WP_DEFAULT,VE32_CELL_MEM_SIMD0_VMEM_ARB_VMEM_WP_RD_MASK,"SRP_BLOCK_VEX_CORE.SIMD0_VMEM_ARB_VMEM_WP");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_CONTROL_BP_CONFIG_OFFSET,VE32_CELL_MEM_LM_ECC_CONTROL_BP_CONFIG_DEFAULT,VE32_CELL_MEM_LM_ECC_CONTROL_BP_CONFIG_RD_MASK,"SRP_BLOCK_VEX_CORE.LM_ECC_CONTROL_BP_CONFIG");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_SBE_IRQPRIO_BP_CONFIG_OFFSET,VE32_CELL_MEM_LM_ECC_SBE_IRQPRIO_BP_CONFIG_DEFAULT,VE32_CELL_MEM_LM_ECC_SBE_IRQPRIO_BP_CONFIG_RD_MASK,"SRP_BLOCK_VEX_CORE.LM_ECC_SBE_IRQPRIO_BP_CONFIG");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_DBE_IRQPRIO_BP_CONFIG_OFFSET,VE32_CELL_MEM_LM_ECC_DBE_IRQPRIO_BP_CONFIG_DEFAULT,VE32_CELL_MEM_LM_ECC_DBE_IRQPRIO_BP_CONFIG_RD_MASK,"SRP_BLOCK_VEX_CORE.LM_ECC_DBE_IRQPRIO_BP_CONFIG");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_SBE_BAD_ADDR_BP_CONFIG_OFFSET,VE32_CELL_MEM_LM_ECC_SBE_BAD_ADDR_BP_CONFIG_DEFAULT,VE32_CELL_MEM_LM_ECC_SBE_BAD_ADDR_BP_CONFIG_RD_MASK,"SRP_BLOCK_VEX_CORE.LM_ECC_SBE_BAD_ADDR_BP_CONFIG");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_DBE_BAD_ADDR_BP_CONFIG_OFFSET,VE32_CELL_MEM_LM_ECC_DBE_BAD_ADDR_BP_CONFIG_DEFAULT,VE32_CELL_MEM_LM_ECC_DBE_BAD_ADDR_BP_CONFIG_RD_MASK,"SRP_BLOCK_VEX_CORE.LM_ECC_DBE_BAD_ADDR_BP_CONFIG");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_SBE_COUNT_BP_CONFIG_OFFSET,VE32_CELL_MEM_LM_ECC_SBE_COUNT_BP_CONFIG_DEFAULT,VE32_CELL_MEM_LM_ECC_SBE_COUNT_BP_CONFIG_RD_MASK,"SRP_BLOCK_VEX_CORE.LM_ECC_SBE_COUNT_BP_CONFIG");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_DBE_COUNT_BP_CONFIG_OFFSET,VE32_CELL_MEM_LM_ECC_DBE_COUNT_BP_CONFIG_DEFAULT,VE32_CELL_MEM_LM_ECC_DBE_COUNT_BP_CONFIG_RD_MASK,"SRP_BLOCK_VEX_CORE.LM_ECC_DBE_COUNT_BP_CONFIG");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_CONTROL_BP_DMEM_OFFSET,VE32_CELL_MEM_LM_ECC_CONTROL_BP_DMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_CONTROL_BP_DMEM_RD_MASK,"SRP_BLOCK_VEX_CORE.LM_ECC_CONTROL_BP_DMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_SBE_IRQPRIO_BP_DMEM_OFFSET,VE32_CELL_MEM_LM_ECC_SBE_IRQPRIO_BP_DMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_SBE_IRQPRIO_BP_DMEM_RD_MASK,"LM_ECC_SBE_IRQPRIO_BP_DMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_DBE_IRQPRIO_BP_DMEM_OFFSET,VE32_CELL_MEM_LM_ECC_DBE_IRQPRIO_BP_DMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_DBE_IRQPRIO_BP_DMEM_RD_MASK,"LM_ECC_DBE_IRQPRIO_BP_DMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_SBE_BAD_ADDR_BP_DMEM_OFFSET,VE32_CELL_MEM_LM_ECC_SBE_BAD_ADDR_BP_DMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_SBE_BAD_ADDR_BP_DMEM_RD_MASK,"LM_ECC_SBE_BAD_ADDR_BP_DMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_DBE_BAD_ADDR_BP_DMEM_OFFSET,VE32_CELL_MEM_LM_ECC_DBE_BAD_ADDR_BP_DMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_DBE_BAD_ADDR_BP_DMEM_RD_MASK,"LM_ECC_DBE_BAD_ADDR_BP_DMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_SBE_COUNT_BP_DMEM_OFFSET,VE32_CELL_MEM_LM_ECC_SBE_COUNT_BP_DMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_SBE_COUNT_BP_DMEM_RD_MASK,"LM_ECC_SBE_COUNT_BP_DMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_DBE_COUNT_BP_DMEM_OFFSET,VE32_CELL_MEM_LM_ECC_DBE_COUNT_BP_DMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_DBE_COUNT_BP_DMEM_RD_MASK,"LM_ECC_DBE_COUNT_BP_DMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_CONTROL_SIMD0_VMEM_OFFSET,VE32_CELL_MEM_LM_ECC_CONTROL_SIMD0_VMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_CONTROL_SIMD0_VMEM_RD_MASK,"LM_ECC_CONTROL_SIMD0_VMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_SBE_IRQPRIO_SIMD0_VMEM_OFFSET,VE32_CELL_MEM_LM_ECC_SBE_IRQPRIO_SIMD0_VMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_SBE_IRQPRIO_SIMD0_VMEM_RD_MASK,"LM_ECC_SBE_IRQPRIO_SIMD0_VMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_DBE_IRQPRIO_SIMD0_VMEM_OFFSET,VE32_CELL_MEM_LM_ECC_DBE_IRQPRIO_SIMD0_VMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_DBE_IRQPRIO_SIMD0_VMEM_RD_MASK,"LM_ECC_DBE_IRQPRIO_SIMD0_VMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_SBE_BAD_ADDR_SIMD0_VMEM_OFFSET,VE32_CELL_MEM_LM_ECC_SBE_BAD_ADDR_SIMD0_VMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_SBE_BAD_ADDR_SIMD0_VMEM_RD_MASK,"LM_ECC_SBE_BAD_ADDR_SIMD0_VMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_DBE_BAD_ADDR_SIMD0_VMEM_OFFSET,VE32_CELL_MEM_LM_ECC_DBE_BAD_ADDR_SIMD0_VMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_DBE_BAD_ADDR_SIMD0_VMEM_RD_MASK,"LM_ECC_DBE_BAD_ADDR_SIMD0_VMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_SBE_COUNT_SIMD0_VMEM_OFFSET,VE32_CELL_MEM_LM_ECC_SBE_COUNT_SIMD0_VMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_SBE_COUNT_SIMD0_VMEM_RD_MASK,"LM_ECC_SBE_COUNT_SIMD0_VMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_ECC_DBE_COUNT_SIMD0_VMEM_OFFSET,VE32_CELL_MEM_LM_ECC_DBE_COUNT_SIMD0_VMEM_DEFAULT,VE32_CELL_MEM_LM_ECC_DBE_COUNT_SIMD0_VMEM_RD_MASK,"LM_ECC_DBE_COUNT_SIMD0_VMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET,VE32_CELL_MEM_LM_BPCA_BP_DMEM_DEFAULT,VE32_CELL_MEM_LM_BPCA_BP_DMEM_RD_MASK,"LM_BPCA_BP_DMEM");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_SEG_BASE_0_BP_XMEM_MASTER_OFFSET,VE32_CELL_MEM_SEG_BASE_0_BP_XMEM_MASTER_DEFAULT,VE32_CELL_MEM_SEG_BASE_0_BP_XMEM_MASTER_RD_MASK,"SEG_BASE_0_BP_XMEM_MASTER");
read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_SEG_BASE_0_SIMD0_XVMEM_MASTER_OFFSET,VE32_CELL_MEM_SEG_BASE_0_SIMD0_XVMEM_MASTER_DEFAULT,VE32_CELL_MEM_SEG_BASE_0_SIMD0_XVMEM_MASTER_RD_MASK,"SEG_BASE_0_SIMD0_XVMEM_MASTER");
}
return 0;




#if 0

error = read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_CONTROL_OFFSET,VE32_CELL_MEM_CONTROL_RD_MASK,VE32_CELL_MEM_CONTROL_DEFAULT, "VE32_CELL_MEM_CONTROL_OFFSET");
error = read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_START_ADDR_OFFSET,VE32_CELL_MEM_START_ADDR_RD_MASK,VE32_CELL_MEM_CONTROL_DEFAULT, "VE32_CELL_MEM_CONTROL_OFFSET");

read_value = read_reg(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET,read_mask, "VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET");
LOG_PRINT("INFO: register %s value  for VEX core no %d is 0x%x\n","VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET",i,  read_value);
write_status = write_reg(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET, write_data, write_mask,"VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET");
LOG_PRINT("INFO: write status to register %s for VEX core no %d is %d","VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET",i,  write_status);
error = read_reg_expect(SRP_BLOCK_VEX_CORE, i,VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET,read_mask,expected_data, "VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET");
}
return 0;
#endif
}



