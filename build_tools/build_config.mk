# =======================================================
# Project Recipes
# =======================================================

build_all : build
	$(info Build All Successful)

build : $(DST_OBJS)
#	@mkdir -p $(^D)
	@$(CPP) $(CXXFLAGS) $^ $(LIB_PATHS) $(LIB_FLAGS) $(CXX_NAME_FLAG) $(OBJ_LOC_NAME)
	$(info Build Successful)

$(PROJECT_DST_DIR)/%$(CXX_OBJ_SUFFIX): $(PROJECT_SRC_DIR)/%.cpp
	$(info Compiling $^)
	@mkdir -p $(@D)
	@$(CPP) $(CXXFLAGS) $(PROJECT_LIB_INCLUDES) $(CXX_COMP_FLAG) $<  $(CXX_NAME_FLAG) $@

# copy_library_files : $(BAKED_LIB_DIR) $(BAKED_INCLUDE_DIR)
# 	@mkdir -p $(PROJECT_INCLUDE_DIR)
# 	@mkdir -p $(PROJECT_DIR)
# 	@cp $(BAKED_LIB_DIR)/*.dll  $(PROJECT_DIR)/
# 	@cp -r $(BAKED_INCLUDE_DIR)/* $(PROJECT_INCLUDE_DIR)/
# 	@cp $(LIBRARY_DEPENDENCIES) $(PROJECT_DIR)/


# # =======================================================
# # Boost Test Recipes
# # =======================================================

# $(PROJECT_TEST_BUILD_DIR)/%.test: $(PROJECT_TEST_BUILD_DIR)/%$(CXX_OBJ_SUFFIX)
# 	@mkdir -p $(@D)
# 	@$(CPP) $(CXXFLAGS) $^ $(PROJECT_SRC_OBJS_TEST) $(PROJECT_LIBS) $(PROJECT_LIB_FLAGS) -o $@

# $(PROJECT_TEST_BUILD_DIR)/%$(CXX_OBJ_SUFFIX): $(PROJECT_TEST_SRC_DIR)/%.cpp
# 	@echo Compiling Test $^
# 	@mkdir -p $(@D)
# 	@$(CPP) $(CXXFLAGS) $(PROJECT_TEST_INCLUDE_PATHS) $(CXX_COMP_FLAG) $< $(CXX_NAME_FLAG) $@


# =======================================================
# Project Clean Recipes
# =======================================================

build_clean: build_clean-exe build_clean-build build_clean_test # build_clean-lib build_clean-include
	$(info Build Clean Successful)

build_clean-exe:
	rm -f $(OBJ_LOC_NAME)

build_clean-build:
	rm -rf $(DST_DIR)

# build_clean-lib:
# 	rm -rf $(PROJECT_DIR)/*.so $(PROJECT_DIR)/*.a $(PROJECT_DIR)/*.dll

# build_clean-include:
# 	rm -rf $(PROJECT_INCLUDE_DIR)

build_clean_test:
	rm -rf $(TEST_BUILD_DIR)


# =======================================================
# Run Test Recipes
# =======================================================

# build_test: run_test

# run_test: $(PROJECT_TEST_TARGETS)
# 	@echo
# 	@for target in $(PROJECT_TEST_TARGETS); do \
# 	echo Running $$target; \
# 	$$target ; \
# 	echo ; \
# 	done
