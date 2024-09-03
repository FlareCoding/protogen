# Makefile for ProtoGen

# Compiler
CC = gcc

# Directories
SRC_DIR = src
BUILD_DIR = build
CMD_DIR = $(SRC_DIR)/commands
UTILS_DIR = $(SRC_DIR)/utils
TEST_DIR = tests

# Compiler Flags
CFLAGS = -Wall -Wextra -I$(SRC_DIR) -std=c11

# Source Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(CMD_DIR)/*.c) $(wildcard $(UTILS_DIR)/*.c)

# Object Files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target Binary
TARGET = $(BUILD_DIR)/protogen

# Test Sources and Binaries
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_BINARIES = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(BUILD_DIR)/test_%)

# Path to Unity source file (for unit tests)
UNITY_SRC = $(TEST_DIR)/unity/unity.c

# Default Target
all: $(TARGET)

# Build Target
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TARGET)

# Compile Sources to Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Test Binaries
build-tests: $(TEST_BINARIES)

$(BUILD_DIR)/test_%: $(TEST_DIR)/%.c $(TARGET)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< $(UNITY_SRC) -o $@

# Run Tests with CWD in the Test Directory
run-tests: build-tests
	@for test_binary in $(TEST_BINARIES); do \
		echo "Running $$test_binary..."; \
		(cd $(BUILD_DIR) && ./`basename $$test_binary`); \
	done

# Clean Target
clean:
	rm -rf $(BUILD_DIR)

# Phony Targets
.PHONY: all clean build-tests run-tests
