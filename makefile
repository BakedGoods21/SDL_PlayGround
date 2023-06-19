# =======================================================
# Variables
# =======================================================

# Sets the root git repo absolute path
TOP_PATH := $(shell git rev-parse --show-toplevel)

# Set bit (Compile 32 or 64 bit binaries)
ifeq ($(BITS),32)
BITS := 32
else
BITS := 64
endif

# Sets RELEASE_MODE which affects various flags
RELEASE_MODE := DEBUG
#RELEASE_MODE := RELEASE # When ready to release

# Set OS Specific Variables
BUILD_TOOLS_DIR := $(TOP_PATH)/build_tools
ifeq ($(OS),Windows_NT)
include $(BUILD_TOOLS_DIR)/win_config.mk
else
include $(BUILD_TOOLS_DIR)/linux_config.mk
endif

include $(BUILD_TOOLS_DIR)/build_config.mk


# =======================================================
# Recipes
# =======================================================

all default : build_all #run_test
	$(info Make All Successful)

clean : build_clean
	$(info Clean All Successful)

print:
	@echo $(LIB_PATH)
