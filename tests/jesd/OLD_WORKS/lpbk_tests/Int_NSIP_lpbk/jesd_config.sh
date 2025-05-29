#JESD IP RX
#l_reg
srpWrite 0x1d08030 0x3
#m_reg
srpWrite 0x1d08038 0x1
#f_reg
srpWrite 0x1d08028 0x7
#s_reg
srpWrite 0x1d08040 0
#n_reg
srpWrite 0x1d08034 0xf
#ntotal_reg
srpWrite 0x1d0803c 0xf
#cs_reg
srpWrite 0x1d08024 0

#SCRATCH
srpWrite 0x1d0a000 0xa
#APB_BRIDGE_STATUS
srpWrite 0x1d0a004 0x8		

#JESD RX GLUE
#WR_POINTER_TBL0[32]
srpWrite 0x1d07300 0x20

#0x01d03400		0x80000000

#JESD RX EN	
srpWrite 0x1d08050 0x1


#JESD TX GLUE
#STRM_ID_TBL0(0)
srpWrite 0x1d05000 0
#STRM_ID_TBL1(0)
srpWrite 0x1d05080 0xfff
#STRM_ID_TBL0(1)
srpWrite 0x1d05004 0x1000
#STRM_ID_TBL1(1)
srpWrite 0x1d05084 0xfff
#STRM_ID_TBL0(2)
srpWrite 0x1d05008 0x2000
#STRM_ID_TBL1(2)
srpWrite 0x1d05088 0xfff
#STRM_ID_TBL0(3)
srpWrite 0x1d0500c 0x3000
#STRM_ID_TBL1(3)
srpWrite 0x1d0508c 0xfff
#STRM_ID_TBL0(4)
srpWrite 0x1d05010 0x4000
#STRM_ID_TBL1(4)
srpWrite 0x1d05090 0xfff
#STRM_ID_TBL0(5)
srpWrite 0x1d05014 0x5000
#STRM_ID_TBL1(5)
srpWrite 0x1d05094 0xfff
#STRM_ID_TBL0(6)
srpWrite 0x1d05018 0x6000
#STRM_ID_TBL1(6)
srpWrite 0x1d05098 0xfff
#STRM_ID_TBL0(7)
srpWrite 0x1d0501c 0x7000
#STRM_ID_TBL1(7)
srpWrite 0x1d0509c 0xfff

#STRM_ID_TBL2[0]
srpWrite 0x1d05200 0
#STRM_ID_TBL2[1]
srpWrite 0x1d05204 0x1
#STRM_ID_TBL2[2]
srpWrite 0x1d05208 0x50
#STRM_ID_TBL2[3]
srpWrite 0x1d0520c 0xf


#JESD IP RX 
#subclass_reg
srpWrite 0x1d0601c 0x1
#fec_enb_reg
srpWrite 0x1d062c4 0x1
#crc12_en_reg
srpWrite 0x1d062cc 0
#bit_order_reg
srpWrite 0x1d062d8 0x3
#e_reg	
srpWrite 0x1d062d4 0
#cf_reg
srpWrite 0x1d06020 0
#hd_reg
srpWrite 0x1d06044 0x1
#crc3_en_reg
srpWrite 0x1d062c8 0
#cmd_enb_reg
srpWrite 0x1d06370 0
#sample_req_reg
srpWrite 0x1d063e0 0
#clk_ratio_reg	
srpWrite 0x1d0613c 0
#l_reg
srpWrite 0x1d06030 0x3
#m_reg
srpWrite 0x1d06038 0x1
#f_reg
srpWrite 0x1d06028 0x7
#s_reg
srpWrite 0x1d06040 0
#sonif_reg
srpWrite 0x1d06368 0x100
#n_reg
srpWrite 0x1d06034 0xf
#ntotal_reg
srpWrite 0x1d0603c 0xf
#cs_reg
srpWrite 0x1d06024 0
#tx_tl_test_mode_reg
srpWrite 0x1d062dc 0

#JESD TX EN
srpWrite 0x1d06050 0x1
 
#JESD LPBK_CTL
srpWrite 0x48.0.0x40 0x1
