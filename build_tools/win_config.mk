# =======================================================
# C++ Variables
# =======================================================

# C++ Variables
CXX := /c/Program\\ Files\\ \\(x86\\)/Microsoft\\ Visual\\ Studio/2022/BuildTools/VC/Tools/MSVC/14.36.32532/bin/HostX64/x64/cl
AR :=
CXXFLAGS := -std:$(CXXSTANDARD) -W4 -EHsc -sdl -options:strict -DWINDOWS

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
SDL_PATH := $(LIB_PATH)/$(SDL_VERSION)
SDL_INCLUDE_PATH := $(SDL_PATH)/include

GLEW_VERSION := glew-2.2.0
GLEW_PATH := $(LIB_PATH)/$(GLEW_VERSION)
GLEW_INCLUDE_PATH := $(GLEW_PATH)/include

GLM_VERSION := glm-0.9.9.8
GLM_PATH := $(LIB_PATH)/$(GLM_VERSION)
GLM_INCLUDE_PATH := $(GLM_PATH)

SDL_MIXER_VERSION := SDL2_mixer-2.6.3
SDL2_MIXER_PATH := $(LIB_PATH)/$(SDL_MIXER_VERSION)
SDL2_INCLUDE_MIXER_PATH := $(SDL2_MIXER_PATH)/include

LIB_PATHS := #-L$(SDL_PATH)/lib/x64 \
			#  -L$(SDL2_MIXER_PATH)/lib/x64 \
			#  -L$(GLEW_PATH)/lib/Release/x64

LIB_FLAGS := $(SDL_PATH)/lib/x64/SDL2.lib \
			 $(SDL2_MIXER_PATH)/lib/x64/SDL2_mixer.lib \
			 $(GLEW_PATH)/lib/Release/x64/glew32.lib \
			 OpenGL32.lib

LIBRARY_DEPENDENCIES := $(SDL_PATH)/lib/x64/SDL2.dll \
						$(GLEW_PATH)/bin/Release/x64/glew32.dll \
						$(SDL2_MIXER_PATH)/lib/x64/SDL2_mixer.dll
