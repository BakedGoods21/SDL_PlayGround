# =======================================================
# Project Recipes
# =======================================================

build_all : copy_library_files build_exe compile_shaders_files
	$(info Build All Successful)

build_exe : $(DST_OBJS)
#	@mkdir -p $(^D)
	$(CXX) $^ $(LIB_PATHS) $(LIB_FLAGS) $(CXX_EXE_NAME_FLAG) $(OBJ_LOC_NAME)
	@echo Build Successful

$(DST_DIR)/%$(CXX_OBJ_SUFFIX) : $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(LIB_INCLUDES) $(CXXFLAGS) -c $< $(CXX_OBJ_NAME_FLAG) $@
	@echo Compiled $<

copy_library_files : $(BAKED_LIB_DIR) $(BAKED_INCLUDE_DIR)
	cp $(LIBRARY_DEPENDENCIES) $(TOP_PATH)
	@echo Copied Dependencies Successfully


compile_shaders_files : $(ALL_SHADER_OBJS)
	@echo Compiled all found shader files

$(SHADER_DST_VERTEX_DIR)/%.spv : $(SHADER_SRC_VERTEX_DIR)/%.vert
	mkdir -p $(@D)
	$(VULKAN_BIN_PATH)/glslc$(CXX_EXE_SUFFIX) $< -o $@
	@echo Compiled Shader $<

$(SHADER_DST_FRAGMENT_DIR)/%.spv : $(SHADER_SRC_FRAGMENT_DIR)/%.frag
	mkdir -p $(@D)
	$(VULKAN_BIN_PATH)/glslc$(CXX_EXE_SUFFIX) $< -o $@
	@echo Compiled Shader $<


# # =======================================================
# # Boost Test Recipes
# # =======================================================

# $(TEST_BUILD_DIR)/%.test: $(TEST_BUILD_DIR)/%$(CXX_OBJ_SUFFIX)
# 	@mkdir -p $(@D)
# 	@$(CXX) $(CXXFLAGS) $^ $(SRC_OBJS_TEST) $(LIBS) $(LIB_FLAGS) -o $@

# $(TEST_BUILD_DIR)/%$(CXX_OBJ_SUFFIX): $(TEST_SRC_DIR)/%.cpp
# 	@echo Compiling Test $^
# 	@mkdir -p $(@D)
# 	@$(CXX) $(CXXFLAGS) $(TEST_INCLUDE_PATHS) $(CXX_COMP_FLAG) $< $(CXX_NAME_FLAG) $@


# =======================================================
# Project Clean Recipes
# =======================================================

build_clean: build_clean_exe build_clean_build  build_clean_lib build_clean_shaders # build_clean_test build_clean_include
	$(info Build Clean Successful)

build_clean_exe:
	rm -f $(OBJ_LOC_NAME)

build_clean_build:
	rm -rf $(DST_DIR)

build_clean_lib:
	rm -rf $(TOP_PATH)/*.so $(TOP_PATH)/*.a $(TOP_PATH)/*.dll $(TOP_PATH)/*.pdb

build_clean_shaders:
	rm -rf $(SHADER_DST_DIR)

# build_clean_include:
# 	rm -rf $(INCLUDE_DIR)

# build_clean_test:
# 	rm -rf $(TEST_BUILD_DIR)


# =======================================================
# Run Test Recipes
# =======================================================

# build_test: run_test

# run_test: $(TEST_TARGETS)
# 	@echo
# 	@for target in $(TEST_TARGETS); do \
# 	echo Running $$target; \
# 	$$target ; \
# 	echo ; \
# 	done

-include $(DEPS)
