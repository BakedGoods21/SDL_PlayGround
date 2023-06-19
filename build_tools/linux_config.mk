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
CXX_COMP_FLAG := -c
CXX_NAME_FLAG := -o
CXX_OBJ_SUFFIX := .o

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


# =======================================================
# Source Variables
# =======================================================

# OBJ_NAME specifies the name of our exectuable/library
OBJ_NAME := test
OBJ_DIR := $(TOP_PATH)
OBJ_LOC_NAME := $(OBJ_DIR)/$(OBJ_NAME)

# Source and destination variables
SRC_DIR := $(TOP_PATH)/src
DST_DIR := $(TOP_PATH)/build
LIB_DIR := $(TOP_PATH)/lib$(BITS)
LIB_DIR_NAME := $(LIB_DIR)/lib$(OBJ_NAME)

# OBJS specifies which files to compile as part of the project
SRC_FILES := $(shell find $(SRC_DIR)/ -name '*.cpp')
DST_OBJS := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(DST_DIR)/%.o)

LIB_PATHS := -L$(SDL_PATH)/lib \
			 -L$(SDL2_MIXER_PATH)/bin \
			 -L$(SDL2_MIXER_PATH)/lib \
			 -L$(GLEW_PATH)/lib

LIB_FLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lopengl32 -lglew32

LIB_INCLUDES := -I$(SDL_PATH)/include \
			    -I$(SDL2_MIXER_PATH)/include \
                -I$(GLEW_PATH)/include \
               	-I$(GLM_PATH) \
				-I$(SRC_DIR)


# =======================================================
# Boost Test Variables
# =======================================================

TEST_SRC_DIR := $(TOP_PATH)/utst
TEST_BUILD_DIR := $(TOP_PATH)/build_utst
TEST_SRC_FILES := $(shell find $(TEST_SRC_DIR)/ -name '*.cpp')
SRC_OBJS_TEST = $(shell find $(shell ls -d $(DST_DIR)/*/*) -name '*.o')
TEST_TARGETS := $(TEST_SRC_FILES:$(TEST_SRC_DIR)/%.cpp=$(TEST_BUILD_DIR)/%.test)
TEST_INCLUDE_PATHS := -I$(TEST_SRC_DIR)/ -I$(SRC_DIR) -I$(LIB_PATH)\boost_1_81_0
