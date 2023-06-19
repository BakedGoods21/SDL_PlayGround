# =======================================================
# C++ Variables
# =======================================================

CPP := g++
AR := ar
CXXFLAGS := -std=c++20 -Wall -Werror -Wextra -Wconversion -Wunused \
   	        -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wcast-align \
           	-Wmissing-field-initializers -fexceptions -fstack-protector-strong \
			--param=ssp-buffer-size=4 -m$(BITS)
# -Wl,-subsystem,windows # Need for later
# -Wold-style-cast -Wshadow
CXX_OBJ_NAME_FLAG := -o:
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
LIB_PATH := C:/Users/warre/Libraries/mingww64

SDL_VERSION := SDL2-2.26.5
SDL_PATH := $(LIB_PATH)/$(SDL_VERSION)/x86_64-w64-mingw32

GLEW_VERSION := glew-2.1.0
GLEW_PATH := $(LIB_PATH)/$(GLEW_VERSION)

GLM_VERSION := glm-0.9.9.8
GLM_PATH := $(LIB_PATH)/$(GLM_VERSION)

SDL_MIXER_VERSION := SDL2_mixer-2.6.3
SDL2_MIXER_PATH := $(LIB_PATH)/$(SDL_MIXER_VERSION)/x86_64-w64-mingw32

LIB_PATHS := -L$(SDL_PATH)/lib \
			 -L$(SDL2_MIXER_PATH)/lib \
			 -L$(GLEW_PATH)/lib

LIB_FLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lopengl32 -lglew32
