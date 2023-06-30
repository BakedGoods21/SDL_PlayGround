# =======================================================
# C++ Variables
# =======================================================

CXX := g++
AR := ar
CXXFLAGS := -std=$(CXXSTANDARD) -Wall -Werror -Wextra -Wconversion -Wunused \
   	        -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wcast-align \
           	-Wmissing-field-initializers -fexceptions -fstack-protector-strong \
			--param=ssp-buffer-size=4 -m$(BITS) -DLINUX -D$(RELEASE_MODE) -Wl,-subsystem,windows -MMD -MP
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
LIB_PATH := $(3RD_PARTY_LIB_DIR)/mingww64
PATH := $(LIB_PATH)/mingw64/bin:$(PATH)
else
LIB_PATH :=
endif

SDL_VERSION := SDL2-2.26.5
SDL_PATH := $(LIB_PATH)/$(SDL_VERSION)/x86_64-w64-mingw32
SDL_INCLUDE_PATH := $(SDL_PATH)/include/SDL2

GLM_VERSION := glm-0.9.9.8
GLM_PATH := $(LIB_PATH)/$(GLM_VERSION)
GLM_INCLUDE_PATH := $(GLM_PATH)

SDL_MIXER_VERSION := SDL2_mixer-2.6.3
SDL2_MIXER_PATH := $(LIB_PATH)/$(SDL_MIXER_VERSION)/x86_64-w64-mingw32
SDL2_INCLUDE_MIXER_PATH := $(SDL2_MIXER_PATH)/include/SDL2

VULKAN_VERSION := VulkanSDK-1.3.250.1
VULKAN_PATH := $(LIB_PATH)/$(VULKAN_VERSION)
VULKAN_INCLUDE_PATH := $(VULKAN_PATH)/Include

LIB_PATHS := -L$(SDL_PATH)/lib \
			 -L$(SDL2_MIXER_PATH)/lib \
			 -L$(GLEW_PATH)/lib \
			 -L$(VULKAN_PATH)/lib
#			  -L$(VULKAN_PATH)/lib

LIB_FLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lvulkan-1

LIBRARY_DEPENDENCIES := $(SDL_PATH)/bin/SDL2.dll \
						$(SDL2_MIXER_PATH)/bin/SDL2_mixer.dll
#						 $(VULKAN_PATH)/bin/
