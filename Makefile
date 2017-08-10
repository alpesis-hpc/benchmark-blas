# BLAS BENCHMARKS
# ------------------------------------------------------------------------------------------------
# directories

# project dirs
PROJECT_DIR = benchmarks
LIB_DIR = $(PROJECT_DIR)/lib
INC_DIR = $(PROJECT_DIR)/inc
SRC_DIR = $(PROJECT_DIR)/src
TESTS_DIR = $(PROJECT_DIR)/tests

# build dirs
BUILD_DIR = _build
BUILD_SRC_DIR = $(BUILD_DIR)/src
BUILD_TESTS_DIR = $(BUILD_DIR)/tests

# ------------------------------------------------------------------------------------------------
# (internal) includes and libs

CLBLAST_INC_DIR = $(LIB_DIR)/clblast/include
CLBLAST_LIB_DIR = $(LIB_DIR)/clblast/lib

# ------------------------------------------------------------------------------------------------
# (external) includes and libs

CUDA_INC_DIR = /usr/local/cuda/include
CUDA_LIB_DIR = /usr/local/cuda/lib64

# ------------------------------------------------------------------------------------------------
# compiler

CC = gcc

CC_OPTS_DEBUG = -std=c99

CC_CFLAGS = $(CC_OPTS_DEBUG) \
            -I$(CUDA_INC_DIR) \
            -I$(CLBLAST_INC_DIR) \
            -I$(INC_DIR)

CC_LDFLAGS = -L$(CUDA_LIB_DIR) -lOpenCL \
             -L$(CLBLAST_LIB_DIR) -lclblast

# ------------------------------------------------------------------------------------------------
# src

SRC_SOURCES := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJECTS := $(patsubst %, $(BUILD_SRC_DIR)/%, $(notdir $(SRC_SOURCES:.c=.o)))

build_srcs: $(SRC_OBJECTS)

$(BUILD_SRC_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "$(RED)Compiling $< $(NC)"
	$(CC) $(CC_CFLAGS) -c $< -o $@

# ------------------------------------------------------------------------------------------------
# tests

TESTS_SOURCES := $(wildcard $(TESTS_DIR)/*.c)
TESTS_OBJECTS := $(patsubst %, $(BUILD_TESTS_DIR)/%, $(notdir $(TESTS_SOURCES:.c=.o)))
TESTS_TARGETS := $(patsubst %, $(BUILD_TESTS_DIR)/%, $(notdir $(TESTS_OBJECTS:.o=)))

run_tests:
	@echo "$(RED) run tests:$(NC)"
	$(foreach test, $(TESTS_TARGETS), \
          $(test) | grep "FAIL"; \
          echo "$(GREEN) TEST $(test)$(NC)";)	
	
build_tests: $(TESTS_TARGETS)

$(BUILD_TESTS_DIR)/% : $(BUILD_TESTS_DIR)/%.o
	@echo "$(RED)Linking $@ $(NC)"
	$(CC) $(CC_CFLAGS) -o $@ $^ $(SRC_OBJECTS) $(CC_LDFLAGS)

$(BUILD_TESTS_DIR)/%.o : $(TESTS_DIR)/%.c
	@echo "$(RED)Compiling $< $(NC)"
	$(CC) $(CC_CFLAGS) -c $< -o $@

# ------------------------------------------------------------------------------------------------
# console

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[1;0m

# ------------------------------------------------------------------------------------------------
# commands

init:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_SRC_DIR)
	mkdir -p $(BUILD_TESTS_DIR)

all: clean init build_srcs build_tests run_tests


clean:
	rm -rf $(BUILD_DIR)	


