#include "init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>    // For error handling
#include <sys/stat.h> // For mkdir function
#include <unistd.h>   // For access function to check directory existence

// Helper function prototypes
void create_makefile(const char *project_name, const char *lang, const char *output_dir);
void create_cmakelists(const char *project_name, const char *lang, const char *type, const char *output_dir);

// Main function to initialize a project
void initialize_project(
    const char *project_name,
    const char *lang,
    const char *type,
    const char *build_system,
    const char *output_dir
) {
    // Create necessary directories
    create_directories(project_name, output_dir);

    // Create initial files (source files, build files)
    create_files(project_name, lang, type, build_system, output_dir);
}

// Helper function to create project directories
void create_directories(
    const char *project_name,
    const char *output_dir
) {
    // Buffer to hold the full path for directory creation
    char path[1024];

    // Check if the output directory exists, create it if it doesn't
    if (access(output_dir, F_OK) == -1) {
        if (mkdir(output_dir, 0755) != 0) {
            perror("Error creating output directory");
            exit(EXIT_FAILURE);
        }
    }

    // Construct the root project directory path
    snprintf(path, sizeof(path), "%s/%s", output_dir, project_name);

    // Create the root project directory
    if (mkdir(path, 0755) != 0) {
        if (errno == EEXIST) {
            fprintf(stderr, "Warning: Project directory '%s' already exists.\n", path);
        } else {
            perror("Error creating project directory");
            exit(EXIT_FAILURE);
        }
    }

    // Create the 'src' subdirectory
    snprintf(path, sizeof(path), "%s/%s/src", output_dir, project_name);
    if (mkdir(path, 0755) != 0) {
        if (errno == EEXIST) {
            fprintf(stderr, "Warning: Directory 'src' already exists.\n");
        } else {
            perror("Error creating 'src' directory");
            exit(EXIT_FAILURE);
        }
    }

    // Create the 'include' subdirectory
    snprintf(path, sizeof(path), "%s/%s/include", output_dir, project_name);
    if (mkdir(path, 0755) != 0) {
        if (errno == EEXIST) {
            fprintf(stderr, "Warning: Directory 'include' already exists.\n");
        } else {
            perror("Error creating 'include' directory");
            exit(EXIT_FAILURE);
        }
    }

    printf("Project directories created successfully in '%s/%s'.\n", output_dir, project_name);
}

// Helper function to create initial project files
void create_files(
    const char *project_name,
    const char *lang,
    const char *type,
    const char *build_system,
    const char *output_dir
) {
    // Create the main entry point file
    generate_main_source_file(project_name, lang, output_dir);

    // Create the necessary files for the build system
    if (strcmp(build_system, "make") == 0) {
        create_makefile(project_name, lang, output_dir);
    } else if (strcmp(build_system, "cmake") == 0) {
        create_cmakelists(project_name, lang, type, output_dir);
    }
}

// Helper function to generate the main source file
void generate_main_source_file(
    const char *project_name,
    const char *lang,
    const char *output_dir
) {
    // Buffer to hold the full path for the main source file
    char path[1024];
    FILE *file;

    // Determine the file extension based on the programming language
    const char *file_extension = (strcmp(lang, "cpp") == 0) ? "cpp" : "c";

    // Construct the full path to the main source file
    snprintf(path, sizeof(path), "%s/%s/src/main.%s", output_dir, project_name, file_extension);

    // Open the file for writing
    file = fopen(path, "w");
    if (file == NULL) {
        perror("Error creating main source file");
        exit(EXIT_FAILURE);
    }

    // Write the "Hello, World!" program to the file
    if (strcmp(lang, "cpp") == 0) {
        // C++ version of the Hello World program
        fprintf(file, "#include <iostream>\n\n");
        fprintf(file, "int main() {\n");
        fprintf(file, "    std::cout << \"Hello, World!\" << std::endl;\n");
        fprintf(file, "    return 0;\n");
        fprintf(file, "}\n");
    } else {
        // C version of the Hello World program
        fprintf(file, "#include <stdio.h>\n\n");
        fprintf(file, "int main() {\n");
        fprintf(file, "    printf(\"Hello, World!\\n\");\n");
        fprintf(file, "    return 0;\n");
        fprintf(file, "}\n");
    }

    // Close the file
    fclose(file);

    printf("Main source file created successfully: %s\n", path);
}

// Helper function to create a Makefile
void create_makefile(const char *project_name, const char *lang, const char *output_dir) {
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s/Makefile", output_dir, project_name);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error creating Makefile");
        exit(EXIT_FAILURE);
    }

    // Determine the compiler based on the language
    const char *compiler = (strcmp(lang, "cpp") == 0) ? "g++" : "gcc";
    const char *src_pattern = (strcmp(lang, "cpp") == 0) ? "*.cpp" : "*.c";

    // Write robust and scalable Makefile content
    fprintf(file, "# Project Name and Directories\n");
    fprintf(file, "PROJECT_NAME = %s\n", project_name);
    fprintf(file, "SRC_DIR = src\n");
    fprintf(file, "INCLUDE_DIR = include\n");
    fprintf(file, "BUILD_DIR = build\n");
    fprintf(file, "BIN_DIR = $(BUILD_DIR)/bin\n");
    fprintf(file, "OBJ_DIR = $(BUILD_DIR)/obj\n\n");

    fprintf(file, "# Compiler and Flags\n");
    fprintf(file, "CC = %s\n", compiler);
    fprintf(file, "CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra\n\n");

    fprintf(file, "# Source Files and Object Files\n");
    fprintf(file, "SRC_FILES = $(wildcard $(SRC_DIR)/%s)\n", src_pattern);
    fprintf(file, "OBJ_FILES = $(patsubst $(SRC_DIR)/%%.%s, $(OBJ_DIR)/%%.o, $(SRC_FILES))\n\n", (strcmp(lang, "cpp") == 0) ? "cpp" : "c");

    fprintf(file, "# Default Target\n");
    fprintf(file, ".PHONY: all\n");
    fprintf(file, "all: $(BIN_DIR)/$(PROJECT_NAME)\n\n");

    fprintf(file, "# Create Build Directories\n");
    fprintf(file, "$(OBJ_DIR):\n");
    fprintf(file, "\tmkdir -p $(OBJ_DIR)\n\n");

    fprintf(file, "$(BIN_DIR):\n");
    fprintf(file, "\tmkdir -p $(BIN_DIR)\n\n");

    fprintf(file, "# Compile Object Files\n");
    fprintf(file, "$(OBJ_DIR)/%%.o: $(SRC_DIR)/%%.%s | $(OBJ_DIR)\n", (strcmp(lang, "cpp") == 0) ? "cpp" : "c");
    fprintf(file, "\t$(CC) $(CFLAGS) -c $< -o $@\n\n");

    fprintf(file, "# Link Object Files to Create Executable or Library\n");
    fprintf(file, "$(BIN_DIR)/$(PROJECT_NAME): $(OBJ_FILES) | $(BIN_DIR)\n");
    fprintf(file, "\t$(CC) $(OBJ_FILES) -o $@\n\n");

    fprintf(file, "# Clean Target\n");
    fprintf(file, ".PHONY: clean\n");
    fprintf(file, "clean:\n");
    fprintf(file, "\trm -rf $(BUILD_DIR)\n");

    fclose(file);
    printf("Makefile created successfully: %s\n", path);
}

// Helper function to create a CMakeLists.txt file
void create_cmakelists(const char *project_name, const char *lang, const char *type, const char *output_dir) {
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s/CMakeLists.txt", output_dir, project_name);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error creating CMakeLists.txt");
        exit(EXIT_FAILURE);
    }

    // Write basic CMakeLists.txt content
    fprintf(file, "cmake_minimum_required(VERSION 3.10)\n");
    fprintf(file, "project(%s)\n", project_name);
    if (strcmp(lang, "cpp") == 0) {
        fprintf(file, "set(CMAKE_CXX_STANDARD 17)\n\n");
    } else {
        fprintf(file, "set(CMAKE_C_STANDARD 99)\n\n");
    }

    const char *file_extension = (strcmp(lang, "cpp") == 0) ? "cpp" : "c";
    if (strcmp(type, "binary") == 0) {
        fprintf(file, "add_executable(%s src/main.%s)\n", project_name, file_extension);
    } else if (strcmp(type, "library") == 0) {
        fprintf(file, "add_library(%s src/main.%s)\n", project_name, file_extension);
    }

    fprintf(file, "target_include_directories(%s PRIVATE include)\n", project_name);

    fclose(file);
    printf("CMakeLists.txt created successfully: %s\n", path);
}

