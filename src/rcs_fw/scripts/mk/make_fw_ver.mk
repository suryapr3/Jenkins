#
# FW version generator
#

GENDIR = $(RCS_FW_DIR)/out/gen/src


#
# Specify FW version major, minor, date,  
#

FW_EB_BUILD ?= 0
C_FW_VER    := $(GENDIR)/fw_ver.c
CURR_DATE    = $(shell date +"%Y-%_m-%_d")
date_tuple  := $(subst -, ,$(CURR_DATE))
CURR_YEAR   := $(word 1, $(date_tuple))
CURR_MONTH  := $(word 2, $(date_tuple))
CURR_DAY    := $(word 3, $(date_tuple))

VER_MAJOR   := $(shell grep ver_major ${PRJDIR}/bldtools/fw_ver.txt | cut -d: -f2 | xargs )
VER_MINOR   := $(shell grep ver_minor ${PRJDIR}/bldtools/fw_ver.txt | cut -d: -f2 | xargs )

CURR_YEAR   := $(shell echo $$(( $(CURR_YEAR) - 2000 )))
FW_EB_BUILD := $(shell echo $$(( $(FW_EB_BUILD) & 1 )))
FW_ITER     := $(shell echo $$(( 0 )) )

FW_VERSION  := 0
FW_VERSION  := $(shell echo "$$(( $(FW_ITER) | $(FW_VERSION) ))" )          # 4 bit iter (bit 0-3)
FW_VERSION  := $(shell echo "$$(( $(FW_EB_BUILD) << 4 | $(FW_VERSION) ))" ) # 1 bit eb_build (bit 4)
FW_VERSION  := $(shell echo "$$(( $(CURR_DAY) << 5 | $(FW_VERSION) ))" )    # 5 bit day (bit 5-9)
FW_VERSION  := $(shell echo "$$(( $(CURR_MONTH) << 10 | $(FW_VERSION) ))" ) # 4 bit month (bit 10-13)
FW_VERSION  := $(shell echo "$$(( $(CURR_YEAR) << 14 | $(FW_VERSION) ))" )  # 8 bit month (bit 14-21)
FW_VERSION  := $(shell echo "$$(( $(VER_MINOR) << 22 | $(FW_VERSION) ))" )  # 6 bit minor (bit 22-27)
FW_VERSION  := $(shell echo "$$(( $(VER_MAJOR) << 28 | $(FW_VERSION) ))" )  # 4 bit major (bit 28-31)

ver: ver_clean
	@mkdir -p $(GENDIR)
	@printf '#include <stdint.h>\n' > $(C_FW_VER)
	@printf '#include "com_rf_def.h"\n\n' >> $(C_FW_VER)
	@printf "ver_fw_t ver_fw = {.value = $(FW_VERSION)};\n" >> $(C_FW_VER)
	@printf '//major:%02d\n' "$(VER_MAJOR)" >> $(C_FW_VER)
	@printf '//minor:%02d\n' "$(VER_MINOR)" >> $(C_FW_VER)
	@printf '//year:%02d\n' "$(CURR_YEAR)" >> $(C_FW_VER)
	@printf '//month:%02d\n' "$(CURR_MONTH)" >> $(C_FW_VER)
	@printf '//day:%02d\n' "$(CURR_DAY)" >> $(C_FW_VER)
	@printf '//eb:%01d\n' "$(FW_EB_BUILD)" >> $(C_FW_VER)
	@printf '//iter:%02d\n' "$(FW_ITER)" >> $(C_FW_VER)

ver_clean:
	@rm -f $(C_FW_VER)

ver_regen_if_needed:
ifeq ("$(wildcard $(C_FW_VER))","")
	@mkdir -p $(GENDIR)
	@printf '#include <stdint.h>\n' > $(C_FW_VER)
	@printf '#include "com_rf_def.h"\n\n' >> $(C_FW_VER)
	@printf "ver_fw_t ver_fw = {.value = $(FW_VERSION)};\n" >> $(C_FW_VER)
	@printf '//major:%02d\n' "$(VER_MAJOR)" >> $(C_FW_VER)
	@printf '//minor:%02d\n' "$(VER_MINOR)" >> $(C_FW_VER)
	@printf '//year:%02d\n' "$(CURR_YEAR)" >> $(C_FW_VER)
	@printf '//month:%02d\n' "$(CURR_MONTH)" >> $(C_FW_VER)
	@printf '//day:%02d\n' "$(CURR_DAY)" >> $(C_FW_VER)
	@printf '//eb:%01d\n' "$(FW_EB_BUILD)" >> $(C_FW_VER)
	@printf '//iter:%02d\n' "$(FW_ITER)" >> $(C_FW_VER)
endif
