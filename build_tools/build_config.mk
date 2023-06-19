# =======================================================
# Project Recipes
# =======================================================

build_all : build
	$(info Build All Successful)

build : $(DST_OBJS)
#	@mkdir -p $(^D)
	$(CPP) $^ $(LIB_PATHS) $(LIB_FLAGS) $(CXX_EXE_NAME_FLAG) $(OBJ_LOC_NAME)
	$(info Build Successful)

$(DST_DIR)/%$(CXX_OBJ_SUFFIX): $(SRC_DIR)/%.cpp
	$(info Compiling $^)
	mkdir -p $(@D)
	$(CPP) $(CXXFLAGS) $(LIB_INCLUDES) -c $< $(CXX_OBJ_NAME_FLAG) $@

# copy_library_files : $(BAKED_LIB_DIR) $(BAKED_INCLUDE_DIR)
# 	@mkdir -p $(INCLUDE_DIR)
# 	@mkdir -p $(DIR)
# 	@cp $(BAKED_LIB_DIR)/*.dll  $(DIR)/
# 	@cp -r $(BAKED_INCLUDE_DIR)/* $(INCLUDE_DIR)/
# 	@cp $(LIBRARY_DEPENDENCIES) $(DIR)/


# # =======================================================
# # Boost Test Recipes
# # =======================================================

# $(TEST_BUILD_DIR)/%.test: $(TEST_BUILD_DIR)/%$(CXX_OBJ_SUFFIX)
# 	@mkdir -p $(@D)
# 	@$(CPP) $(CXXFLAGS) $^ $(SRC_OBJS_TEST) $(LIBS) $(LIB_FLAGS) -o $@

# $(TEST_BUILD_DIR)/%$(CXX_OBJ_SUFFIX): $(TEST_SRC_DIR)/%.cpp
# 	@echo Compiling Test $^
# 	@mkdir -p $(@D)
# 	@$(CPP) $(CXXFLAGS) $(TEST_INCLUDE_PATHS) $(CXX_COMP_FLAG) $< $(CXX_NAME_FLAG) $@


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
# 	rm -rf $(DIR)/*.so $(DIR)/*.a $(DIR)/*.dll

# build_clean-include:
# 	rm -rf $(INCLUDE_DIR)

build_clean_test:
	rm -rf $(TEST_BUILD_DIR)


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
