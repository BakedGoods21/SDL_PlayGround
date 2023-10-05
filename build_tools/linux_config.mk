# =======================================================
# C++ Variables
# =======================================================

CXX := g++
AR := ar
CXXFLAGS := -std=$(CXXSTANDARD) -MMD -MP -Wall -Wextra -Werror -pedantic-errors \
   	        -Wconversion -Wunused -Wpointer-arith -Wcast-qual -Wno-missing-braces \
           	-Wcast-align -Wmissing-field-initializers -fexceptions -fstack-protector-strong \
			--param=ssp-buffer-size=4 -m$(BITS) -DLINUX -D$(RELEASE_MODE)
# -Wl,-subsystem,windows # Need for later
# -Wold-style-cast -Wshadow
CXX_OBJ_NAME_FLAG := -o
CXX_EXE_NAME_FLAG := $(CXX_OBJ_NAME_FLAG)
CXX_OBJ_SUFFIX := .o
CXX_EXE_SUFFIX :=

# Set Release mode specific compiler flags
ifeq ($(RELEASE_MODE),RELEASE)
CXXFLAGS += -O3
else
CXXFLAGS += -g
endif


# =======================================================
# Library Dependencies
# =======================================================

# Sets the Library Path location
ifeq ($(OS),Windows_NT)
LIB_PATH := $(3RD_PARTY_LIB_DIR)/windows
PATH := $(LIB_PATH)/mingw64/bin:$(PATH)
CXXFLAGS += -Wl,-subsystem,windows
else
LIB_PATH :=
endif

SDL_VERSION := SDL2-2.26.5
SDL_PATH := $(LIB_PATH)/$(SDL_VERSION)/build-install
SDL_INCLUDE_PATH := $(SDL_PATH)/include/SDL2

GLM_VERSION := glm-0.9.9.8
GLM_PATH := $(LIB_PATH)/$(GLM_VERSION)
GLM_INCLUDE_PATH := $(GLM_PATH)

VULKAN_VERSION := VulkanSDK-1.3.250.1
VULKAN_PATH := $(LIB_PATH)/$(VULKAN_VERSION)
VULKAN_INCLUDE_PATH := $(VULKAN_PATH)/Include
VULKAN_BIN_PATH := $(VULKAN_PATH)/Bin
# TODO: Figure out linux vulkan bin path for exe's like glslc

LIB_PATHS := -L$(SDL_PATH)/lib \
			 -L$(VULKAN_PATH)/lib

LIB_FLAGS := -lmingw32 -lSDL2 -lvulkan-1

LIBRARY_DEPENDENCIES := $(SDL_PATH)/bin/SDL2.dll
