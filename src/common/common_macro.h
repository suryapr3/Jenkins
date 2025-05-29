//18a Rcs Mem
#define       RCS_ROM_MEM_SIZE          0x00100000       /* 0x10 , 1MB */

#define       RCS_CORE_CTRL_START       0x000c0000       /* 0x11.i = 0..1  */
#define       RCS_CORE_CTRL_SIZE        0x00040000       /* 256KB/per instance */

#define       RCS_CORE_CALIB_START      0x00180000       /* 0x12.i = 0  512K*/
#define       RCS_CORE_CALIB_SIZE       0x00080000       /* 0x12.i = 0  512K*/

#define       RCS_RSM_START             0x00200000       /* 0x13 i = 0..1 */
#define       RCS_RSM_SIZE              0x00020000       /* 128K/per instance */

//18a Vex Mem
#define       VEX_DMEM_START            0x02804000
#define       VEX_DMEM_OFFSET           0x40000
#define       VEX_DMEM_SIZE             0x4000           /*DMEM 16K */

#define       VEX_PMEM_START            0x02808000
#define       VEX_PMEM_OFFSET           0x40000          /* 0x63.i = 0..39 */
#define       VEX_PMEM_SIZE             0x10000          /* 64K*/

#define       VEX_VMEM_START            0x02828000
#define       VEX_VMEM_OFFSET           0x40000
#define       VEX_VMEM_SIZE             0x10000          /* 64K*/

// 18a DRF Mem
#define       DRF_CMEM_START            0x05000000
#define       DRF_CMEM_SIZE             0x10000         /* 128 K Byte */
#define       DRF_CMEM_OFFSET           0X40000

#define       DRF_SRAM_START            0x04400000
#define       DRF_SRAM_SIZE             0x10000         /*256 K Byte */

#define       DRF_SRAM_CAP_START        0x04000000
#define       DRF_SRAM_CAP_SIZE         0x10000         /* 128 K Byte */

#define       DRF_ADC_CPU_START         0x049a0000
#define       DRF_ADC_CPU_SIZE          0x10000         /* 128 K Byte */

#define       DRF_DESC_START            0x04510000
#define       DRF_DESC_SIZE             0x4000          /*6 K Byte*/
//

#define       MEM_ACCESS_SIZE           0x1000
#define       FRIO                      TRUE


