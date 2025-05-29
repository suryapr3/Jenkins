################################################################################################### 
# 
# INTEL CONFIDENTIAL 
# 
# Copyright (C) 2022 Intel Corporation 
# 
# This software and the related documents ("Material") are Intel copyrighted materials, 
# and your use of them is governed by the express license under which they were provided 
# to you ("License"). Unless the License provides otherwise, you may not use, modify, 
#* copy, publish, distribute, disclose or transmit this software or the related documents 
# without Intel's prior written permission. 
# This software and the related documents are provided as is, with no express or implied 
# warranties, other than those that are expressly stated in the License. 
# No license under any patent, copyright, trade secret or other intellectual property 
# right is granted to or conferred upon you by disclosure or delivery of the Materials, 
# either expressly, by implication, inducement, estoppel or otherwise. Any license under 
# such intellectual property rights must be expressed and approved by Intel in writing. 
# 
###################################################################################################

.PHONY: lock clean lock_sim lock_hw lock_hw_clean lock_sim_clean nleq nleq_sim nleq_hw nleq_hw_clean nleq_sim_clean eigentest_sim_clean eigentest_hw_clean

lock: lock_hw lock_sim
nleq: nleq_hw nleq_sim
eigentest: eigentest_hw eigentest_sim 
lock_clean: lock_hw_clean lock_sim_clean
nleq_clean: nleq_hw_clean nleq_sim_clean
eigentest_clean: eigentest_hw_clean eigentest_sim_clean
lock_sim:
	$(MAKE) -C lock TARGET=sim
lock_hw:
	$(MAKE) -C lock TARGET=hw
nleq_sim:
	$(MAKE) -C nleq TARGET=sim
nleq_hw:
	$(MAKE) -C nleq TARGET=hw	
eigentest_hw:
	$(MAKE) -C eigentest TARGET=hw
eigentest_sim:
	$(MAKE) -C eigentest TARGET=sim
lock_sim_clean:
	$(MAKE) -C lock TARGET=sim clean
lock_hw_clean:
	$(MAKE) -C lock TARGET=hw clean
nleq_sim_clean:
	$(MAKE) -C nleq TARGET=sim clean
nleq_hw_clean:
	$(MAKE) -C nleq TARGET=hw clean
eigentest_hw_clean:
	$(MAKE) -C eigentest TARGET=hw clean	
eigentest_sim_clean:
	$(MAKE) -C eigentest TARGET=sim clean		