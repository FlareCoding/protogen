# Makefile for ProtoGen

# Compiler
CC = gcc

# Directories
SRC_DIR = src
BUILD_DIR = build
CMD_DIR = $(SRC_DIR)/commands
UTILS_DIR = $(SRC_DIR)/utils

# Compiler Flags
CFLAGS = -Wall -Wextra -I$(SRC_DIR) -std=c11

# Source Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(CMD_DIR)/*.c) $(wildcard $(UTILS_DIR)/*.c)

# Object Files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target Binary
TARGET = $(BUILD_DIR)/protogen

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

# Clean Target
clean:
	rm -rf $(BUILD_DIR)

# Phony Targets
.PHONY: all clean
