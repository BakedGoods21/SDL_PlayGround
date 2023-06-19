# =======================================================
# Source Variables
# =======================================================

# OBJ_NAME specifies the name of our exectuable/library
OBJ_NAME := test$(CXX_EXE_SUFFIX)
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

LIB_INCLUDES := -I$(SDL_PATH)/include \
			    -I$(SDL2_MIXER_PATH)/include \
                -I$(GLEW_PATH)/include \
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
