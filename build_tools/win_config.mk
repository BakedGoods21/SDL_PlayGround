# =======================================================
# C++ Variables
# =======================================================

# C++ Variables
CPP := /c/Program\\ Files\\ \\(x86\\)/Microsoft\\ Visual\\ Studio/2022/BuildTools/VC/Tools/MSVC/14.36.32532/bin/HostX64/x64/cl
AR :=
CXXFLAGS := -EHsc#-std:c++20 -Wall -WX -sdl -options:strict

ifeq ($(RELEASE_MODE),RELEASE)
CXXFLAGS += -O2
else
CXXFLAGS += #-Zi
endif

CXX_OBJ_NAME_FLAG := -Fo:
CXX_EXE_NAME_FLAG := -Fe:
CXX_OBJ_SUFFIX := .obj
CXX_EXE_SUFFIX := .exe


# =======================================================
# Build Tool Variables
# =======================================================

# Set BUILD_TOOL according to which system to use while building
BUILD_TOOL := WINDOWS
# BUILD_TOOL := MINGW64 # Other option

# Sets the Library Path location
ifeq ($(BUILD_TOOL),WINDOWS)
LIB_PATH := C:/Users/warre/Libraries/windows
else ifeq ($(BUILD_TOOL),MINGW64)
LIB_PATH := C:/Users/warre/Libraries/mingww64
else
$(info "Incorrect BUILD_TOOL set, use WINDOWS or MINGW64")
exit
endif


# =======================================================
# Library Dependencies
# =======================================================

SDL_VERSION := SDL2-2.26.5
SDL_PATH := $(LIB_PATH)/$(SDL_VERSION)

GLEW_VERSION := glew-2.2.0
GLEW_PATH := $(LIB_PATH)/$(GLEW_VERSION)

GLM_VERSION := glm-0.9.9.8
GLM_PATH := $(LIB_PATH)/$(GLM_VERSION)

SDL_MIXER_VERSION := SDL2_mixer-2.6.3
SDL2_MIXER_PATH := $(LIB_PATH)/$(SDL_MIXER_VERSION)

LIB_PATHS := #-L$(SDL_PATH)/lib/x64 \
			#  -L$(SDL2_MIXER_PATH)/lib/x64 \
			#  -L$(GLEW_PATH)/lib/Release/x64

LIB_FLAGS := $(SDL_PATH)/lib/x64/SDL2.lib \
			 $(SDL2_MIXER_PATH)/lib/x64/SDL2_mixer.lib \
			 $(GLEW_PATH)/lib/Release/x64/glew32.lib
