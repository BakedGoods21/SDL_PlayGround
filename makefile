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

printvars:
	@printf "\
	    TOP_PATH: $(TOP_PATH)\n\
	    3RD_PARTY_LIB_DIR: $(3RD_PARTY_LIB_DIR)\n\
	    BITS: $(BITS)\n\
	    RELEASE_MODE: $(RELEASE_MODE)\n\
	    BUILD_TOOLS_DIR: $(BUILD_TOOLS_DIR)\n\
	    BUILD_TOOL: $(BUILD_TOOL)\n\
	    \n\
	    CXX: $(CXX)\n\
	    AR: $(AR)\n\
	    CXXFLAGS: $(CXXFLAGS)\n\
	    CXX_OBJ_NAME_FLAG: $(CXX_OBJ_NAME_FLAG)\n\
	    CXX_EXE_NAME_FLAG: $(CXX_EXE_NAME_FLAG)\n\
	    CXX_OBJ_SUFFIX: $(CXX_OBJ_SUFFIX)\n\
	    CXX_EXE_SUFFIX: $(CXX_EXE_SUFFIX)\n\
	    \n\
	    SDL_VERSION: $(SDL_VERSION)\n\
	    SDL_PATH: $(SDL_PATH)\n\
	    SDL_INCLUDE_PATH: $(SDL_INCLUDE_PATH)\n\
	    \n\
	    GLEW_VERSION: $(GLEW_VERSION)\n\
	    GLEW_PATH: $(GLEW_PATH)\n\
	    GLEW_INCLUDE_PATH: $(GLEW_INCLUDE_PATH)\n\
	    \n\
	    GLM_VERSION: $(GLM_VERSION)\n\
	    GLM_PATH: $(GLM_PATH)\n\
	    GLM_INCLUDE_PATH: $(GLM_INCLUDE_PATH)\n\
	    \n\
	    SDL_MIXER_VERSION: $(SDL_MIXER_VERSION)\n\
	    SDL2_MIXER_PATH: $(SDL2_MIXER_PATH)\n\
	    SDL2_INCLUDE_MIXER_PATH: $(SDL2_INCLUDE_MIXER_PATH)\n\
	    \n\
	    LIB_PATHS: $(LIB_PATHS)\n\
	    LIB_FLAGS: $(LIB_FLAGS)\n\
	    LIBRARY_DEPENDENCIES: $(LIBRARY_DEPENDENCIES)\n\
	    \n\
	    OBJ_NAME: $(OBJ_NAME)\n\
	    OBJ_DIR: $(OBJ_DIR)\n\
	    OBJ_LOC_NAME: $(OBJ_LOC_NAME)\n\
	    SRC_DIR: $(SRC_DIR)\n\
	    DST_DIR: $(DST_DIR)\n\
	    LIB_DIR: $(LIB_DIR)\n\
	    LIB_DIR_NAME: $(LIB_DIR_NAME)\n\
	    \n\
	    SRC_FILES: $(SRC_FILES)\n\
	    \n\
	    DST_OBJS: $(DST_OBJS)\n\
	    \n\
	    LIB_INCLUDES: $(LIB_INCLUDES)\n\
	    \n\
	    Note: All variables can be overridden by \"<variable>=<new_string>\"\n\
	          Modify 3RD_PARTY_LIB_DIR variable to corresponding directory path with appropriate libraries to compile with this makefile"

help :
	@printf "\
	Usage: make <target> [options]...\n\
	\n\
	Targets:\n\
	    all (default)    Build executable (debug mode by default) (default target)\n\
	    help             Print this information\n\
	    printvars        Print Makefile variables for debugging\n\
	\n\
	Options:\n\
	    RELEASE_MODE=<option>    Run target using following configuration. DEBUG is default behavior\n\
	        DEBUG (default)    Generates symbols for debugging purposes\n\
	        RELEASE            Disables symbols and compiles with optimization flags\n\
	    BITS=<option>    Build for 32/64-bit Windows (Windows MVSC - vcvars64.bat or vcvars32.bat needs to be ran prior to make respectively)\n\
	        64 (default)    Build a 64 bit binary\n\
	        32              Build a 32 bit binary\n\
	    BUILD_TOOL=<option>    Which C++ build tool to use\n\
	        WINDOWS    Build using Windows MSVC buildtools (Need to run vcvars64.bat or vcvars32.bat prior to make respectively)\n\
	        LINUX      Will build using either mingww64 if on windows or g++ if on Linux\n\
	\n\
	Note:\n\
	    vcvars64.bat and vcvars32.bat is typically located: C:\Program Files (x86)\Microsoft Visual Studio\<Year>\BuildTools\VC\Auxiliary\Build\n\
	    The above options affect all and printvars targets\n\
	    All variables can be overridden by \"<variable>=<new_string>\"\n\
	    Modify 3RD_PARTY_LIB_DIR variable to corresponding directory path with appropriate libraries to compile with this makefile\n"
