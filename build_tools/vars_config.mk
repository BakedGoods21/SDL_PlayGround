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

# Shader source and destination variables
SHADER_DIR := $(TOP_PATH)/resources/Shaders
SHADER_SRC_DIR := $(SHADER_DIR)/src
SHADER_DST_DIR := $(SHADER_DIR)/build

SHADER_SRC_VERTEX_DIR := $(SHADER_SRC_DIR)/Vertex
SHADER_SRC_FRAGMENT_DIR := $(SHADER_SRC_DIR)/Fragment

SHADER_DST_VERTEX_DIR := $(SHADER_DST_DIR)/Vertex
SHADER_DST_FRAGMENT_DIR := $(SHADER_DST_DIR)/Fragment

# OBJS specifies which files to compile as part of the project
SRC_FILES := $(shell find $(SRC_DIR)/ -name '*.cpp')
DST_OBJS := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(DST_DIR)/%$(CXX_OBJ_SUFFIX))
DEPS := $(DST_OBJS:%$(CXX_OBJ_SUFFIX)=%.d)

# OBJS specifies which shader files to compile as part of the project
SHADER_VERTEX_FILES := $(shell find $(SHADER_SRC_VERTEX_DIR)/ -name '*.vert')
SHADER_FRAGMENT_FILES := $(shell find $(SHADER_SRC_FRAGMENT_DIR)/ -name '*.frag')
ALL_SHADER_FILES := $(SHADER_VERTEX_FILES) $(SHADER_FRAGMENT_FILES)
VERTEX_SHADER_OBJS := $(SHADER_VERTEX_FILES:$(SHADER_SRC_VERTEX_DIR)/%.vert=$(SHADER_DST_VERTEX_DIR)/%.spv)
FRAGMENT_SHADER_OBJS := $(SHADER_FRAGMENT_FILES:$(SHADER_SRC_FRAGMENT_DIR)/%.frag=$(SHADER_DST_FRAGMENT_DIR)/%.spv)
ALL_SHADER_OBJS := $(VERTEX_SHADER_OBJS) $(FRAGMENT_SHADER_OBJS)

# Libraries to add to the include
LIB_INCLUDES := -I$(SDL_INCLUDE_PATH) \
			    -I$(SDL2_INCLUDE_MIXER_PATH) \
               	-I$(GLM_INCLUDE_PATH) \
				-I$(VULKAN_INCLUDE_PATH) \
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
