# =======================================================
# Variables
# =======================================================

# Sets the root git repo absolute path
TOP_PATH := $(shell git rev-parse --show-toplevel)
3RD_PARTY_LIB_DIR := C:/Users/warre/Libraries

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

# Set BUILD_TOOL according to which system to use while building
ifeq ($(OS),Windows_NT)
BUILD_TOOL := WINDOWS
else
BUILD_TOOL := LINUX
endif
# BUILD_TOOL := LINUX # Other option

ifeq ($(BUILD_TOOL),WINDOWS)
include $(BUILD_TOOLS_DIR)/win_config.mk
else ifeq ($(BUILD_TOOL),LINUX)
include $(BUILD_TOOLS_DIR)/linux_config.mk
else
$(info "Incorrect BUILD_TOOL set, use WINDOWS or LINUX")
exit
endif

include $(BUILD_TOOLS_DIR)/vars_config.mk
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
