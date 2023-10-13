# =======================================================
# C++ Variables
# =======================================================

# C++ Variables
CXX := /c/Program\\ Files\\ \\(x86\\)/Microsoft\\ Visual\\ Studio/2022/BuildTools/VC/Tools/MSVC/14.36.32532/bin/HostX64/x64/cl
AR :=
CXXFLAGS := -std:$(CXXSTANDARD) -W4 -EHsc -sdl -options:strict -DWINDOWS -D$(RELEASE_MODE)

ifeq ($(RELEASE_MODE),RELEASE)
CXXFLAGS += -O2
else
CXXFLAGS += -Zi
endif

CXX_OBJ_NAME_FLAG := -Fo:
CXX_EXE_NAME_FLAG := -Fe:
CXX_OBJ_SUFFIX := .obj
CXX_EXE_SUFFIX := .exe


# =======================================================
# Build Tool Variables
# =======================================================

# Sets the Library Path location
LIB_PATH :=$(3RD_PARTY_LIB_DIR)/windows


# =======================================================
# Library Dependencies
# =======================================================

SDL_VERSION := SDL2-2.26.5
SDL_PATH := $(LIB_PATH)/$(SDL_VERSION)/build_install
SDL_INCLUDE_PATH := $(SDL_PATH)/include/SDL2
SDL_LIB_PATH := $(SDL_PATH)/lib
SDL_LIB_FILE := $(SDL_LIB_PATH)/SDL2.lib

GLM_VERSION := glm-0.9.9.8
GLM_PATH := $(LIB_PATH)/$(GLM_VERSION)
GLM_INCLUDE_PATH := $(GLM_PATH)

VULKAN_VERSION := VulkanSDK-1.3.250.1
VULKAN_PATH := $(LIB_PATH)/$(VULKAN_VERSION)
VULKAN_INCLUDE_PATH := $(VULKAN_PATH)/Include
VULKAN_BIN_PATH := $(VULKAN_PATH)/Bin
VULKAN_LIB_PATH := $(VULKAN_PATH)/lib
VULKAN_LIB_FILE := $(VULKAN_LIB_PATH)/vulkan-1.lib

LIB_PATHS := #-L$(SDL_PATH)/lib/x64 \
			#  -L$(SDL2_MIXER_PATH)/lib/x64 \
#			   -L$(VULKAN_PATH)/lib

LIB_FLAGS := $(SDL_LIB_FILE) \
			 $(VULKAN_LIB_FILE) \
			 OpenGL32.lib

LIBRARY_DEPENDENCIES := $(SDL_PATH)/bin/SDL2.dll 
#						 $(VULKAN_PATH)/bin/
