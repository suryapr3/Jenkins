#
# Coverity related targets
#

# Coverity specific variables.
ifneq ($(IWA_GIT_BRANCH),)
    COV_BRANCH = $(IWA_GIT_BRANCH)
else
    COV_BRANCH = DEV
endif

COV_PROJECT    ?=  Rcs-Arborcrest-FW
COV_TOOLS      ?=  /tools/AGRtools/coverity/current/analysis
COV_TMPDIR     ?=  out/cov.tmpdir
COV_HTML_DIR   ?=  out/coverity.html
COV_URL        ?=  https://coverityent.devtools.intel.com/prod7
COV_STREAM     ?=  $(COV_PROJECT)-$(COV_BRANCH)
COV_TARGETS    ?=  all
COV_SERVER_KEY ?=  /home/sys_swbuilds/.cov_prod7key
COV_COMMIT_MSG ?=  "Commit ID $(ABCFW_COMMIT_ID)"
COV_JSON       ?= $(COV_TMPDIR)/cov_analyze.json
COV_ERROR_TXT  ?= $(COV_TMPDIR)/cov_error.txt
COV_IMPACT_LEVEL   ?= High
COV_INPUT_FILELIST ?= $(COV_TMPDIR)/cov_input_filelist.txt
COV_UPDATE_TYPEDEFS ?= $(COV_TOOLS)/config/templates/xtensa_clang


PATH           :=  $(PATH):$(COV_TOOLS)/bin
HTTP_PROXY     ?=  http://proxy-chain.intel.com:912
FTP_PROXY      ?=  http://proxy-chain.intel.com:912
SOCKS_PROXY    ?=  http://proxy-chain.intel.com:1080
HTTPS_PROXY    ?=  http://proxy-chain.intel.com:912
NO_PROXY       ?=  localhost,127.0.0.1/8,127.0.0.0/8,10.0.0.0/8,172.16.0.0/20,192.168.0.0/16,*.intel.com


export PATH HTTP_PROXY FTP_PROXY SOCKS_PROXY HTTPS_PROXY NO_PROXY

.PHONY: cov_configure cov_build cov_analyze cov_commit cov_clean \
        cov_create_stream cov_run_desktop

cov_configure:
	cov-configure --template --compiler xt-clang --comptype xtclang ; \
	cov-configure --template --compiler clang-10 --comptype xtclang
	@if [ -f $(COV_UPDATE_TYPEDEFS)/compiler-compat-xtensaclang-common_original.h.bak ]; then \
		echo "file updated - no patching required"; \
	else \
		cp $(COV_UPDATE_TYPEDEFS)/compiler-compat-xtensaclang-common.h $(COV_UPDATE_TYPEDEFS)/compiler-compat-xtensaclang-common_original.h.bak; \
		patch $(COV_UPDATE_TYPEDEFS)/compiler-compat-xtensaclang-common.h scripts/mk/cov_xtensa_clang.patch; \
	fi

cov_clean:
	rm -rf $(COV_TMPDIR); \
	rm -rf $(COV_HTML_DIR)
	
cov_build:
	$(MAKE) clean ; \
	cov_clean ; \
	cov-build --dir $(COV_TMPDIR) $(MAKE) $(COV_TARGETS)

cov_rebuild:
	cov-build --dir $(COV_TMPDIR) $(MAKE) $(COV_TARGETS)

cov_analyze:
	cov-analyze --dir $(COV_TMPDIR) --concurrency     \
	            --security --rule                                       \
	            --enable-constraint-fpp --enable-fnptr --enable-virtual \
                    --strip-path $(RCS_FW_DIR)/                           ; \
	cov-format-errors --dir $(COV_TMPDIR)             \
	            --html-output $(COV_HTML_DIR)

cov_commit: cov_create_stream
ifneq ($(COV_BRANCH),DEV)
	echo "INFO: Committing results to the $(COV_STREAM)"
	cov-commit-defects                 \
	                   --auth-key-file $(COV_SERVER_KEY) \
	                   --dir $(COV_TMPDIR)               \
			   --stream $(COV_STREAM)            \
                           --description $(COV_COMMIT_MSG)   \
			   --url $(COV_URL)
endif

cov_create_stream:
	COV_STREAM_EXISTS=$(shell $(COV_TOOLS)/bin/cov-manage-im         \
	                          --auth-key-file $(COV_SERVER_KEY)       \
                                  --url $(COV_URL) --mode projects        \
				  --name $(COV_PROJECT) --show            \
				  --stream $(COV_STREAM) --fields Project \
                                | grep $(COV_PROJECT)) ;                  \
	if [ x"$$COV_STREAM_EXISTS" = x"" ]; then  \
            echo "INFO: Creating the stream $(COV_STREAM)" ; \
            cov-manage-im --auth-key-file $(COV_SERVER_KEY) --mode streams \
                          --add --set name\:$(COV_STREAM) --set lang\:"C/C++" \
                          --set desc\:"Arborcrest stream for $(COV_BRANCH) branch" \
                          --url $(COV_URL) ; \
            cov-manage-im --auth-key-file $(COV_SERVER_KEY) \
	                  --mode projects                                     \
                          --name $(COV_PROJECT) --update                      \
			  --insert stream:$(COV_STREAM) --url $(COV_URL) ;    \
            echo "INFO: Stream : $(COV_STREAM) created" ; \
        else \
            echo "INFO: Updating the results to the stream : $(COV_STREAM)" ; \
        fi


cov_run_desktop:
	echo "INFO: Running cov run desktop for premerge"
ifneq ($(COV_INPUT_FILELIST),)
	cov-run-desktop --url $(COV_URL) --auth-key-file $(COV_SERVER_KEY) \
                        --stream $(COV_STREAM) --dir $(COV_TMPDIR) --impact-regex $(COV_IMPACT_LEVEL) \
			--delete-stale-tus --present-in-reference false \
			--reference-snapshot latest --ignore-uncapturable-inputs true \
                        --json-output-v9 $(COV_JSON) --text-output $(COV_ERROR_TXT) --text-output-style oneline  \
			"@UTF-8@$(COV_INPUT_FILELIST)"
else
	echo "ERROR: COV_INPUT_FILELIST is not present. \
	      Execute export COV_INPUT_FILELIST=<path to filelist> before calling $@"
endif
