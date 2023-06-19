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


# =======================================================
# Source Variables
# =======================================================

# OBJ_NAME specifies the name of our exectuable/library
OBJ_NAME := test.exe
OBJ_DIR := $(TOP_PATH)
OBJ_LOC_NAME := $(OBJ_DIR)/$(OBJ_NAME)

# Source and destination variables
SRC_DIR := $(TOP_PATH)/src
DST_DIR := $(TOP_PATH)/build
LIB_DIR := $(TOP_PATH)/lib$(BITS)
LIB_DIR_NAME := $(LIB_DIR)/lib$(OBJ_NAME)

# OBJS specifies which files to compile as part of the project
SRC_FILES := $(shell find $(SRC_DIR)/ -name '*.cpp')
DST_OBJS := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(DST_DIR)/%$(CXX_OBJ_SUFFIX))

LIB_PATHS := #-L$(SDL_PATH)/lib \
# 			 -L$(SDL2_MIXER_PATH)/bin \
# 			 -L$(SDL2_MIXER_PATH)/lib \
# 			 -L$(GLEW_PATH)/lib

LIB_FLAGS := #/link \
			 #$(SDL_PATH)/SDL2.dll \
			 #$(SDL2_MIXER_PATH)/SDL2_mixer.dll \
			 #$(GLEW_PATH)/bin/Release/x64/glew32.dll

LIB_INCLUDES := -I$(GLEW_PATH)/include \
				-I$(GLM_PATH) \
				-I$(SRC_DIR)


# =======================================================
# Boost Test Variables
# =======================================================

# TEST_SRC_DIR := $(TOP_PATH)/utst
# TEST_BUILD_DIR := $(TOP_PATH)/build_utst
# TEST_SRC_FILES := $(shell find $(TEST_SRC_DIR)/ -name '*.cpp')
# SRC_OBJS_TEST = $(shell find $(shell ls -d $(DST_DIR)/*/*) -name '*.obj')
# TEST_TARGETS := $(TEST_SRC_FILES:$(TEST_SRC_DIR)/%.cpp=$(TEST_BUILD_DIR)/%.test)
# TEST_INCLUDE_PATHS := /I$(TEST_SRC_DIR) /I$(SRC_DIR) /I$(LIB_PATH)/boost_1_81_0
