#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands/init.h"

// Function declarations
void print_general_usage();
void print_init_usage();
void print_add_usage();
void handle_init(int argc, char *argv[]);
void handle_add(int argc, char *argv[]);
void handle_version();

// Main function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_general_usage();
        return 0;
    }

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_general_usage();
        return 0;
    } else if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
        handle_version();
        return 0;
    } else if (strcmp(argv[1], "init") == 0) {
        if (argc == 3 && strcmp(argv[2], "--help") == 0) {
            print_init_usage();
            return 0;
        }
        handle_init(argc - 1, &argv[1]);
        return 0;
    } else if (strcmp(argv[1], "add") == 0) {
        if (argc == 3 && strcmp(argv[2], "--help") == 0) {
            print_add_usage();
            return 0;
        }
        handle_add(argc - 1, &argv[1]);
        return 0;
    }

    printf("Unknown command: %s\n", argv[1]);
    printf("Use 'protogen --help' to see available commands.\n");
    return 1;
}

// Function to print general usage information
void print_general_usage() {
    printf("ProtoGen - A CLI tool for generating C/C++ project templates\n\n");
    printf("Usage:\n");
    printf("  protogen <command> [options]\n\n");
    printf("Commands:\n");
    printf("  %-30s %s\n", "protogen --help", "Displays help information.");
    printf("  %-30s %s\n", "protogen init <project-name>", "Initializes a new project.");
    printf("    %-28s %s\n", "--lang <c|cpp>", "Specifies the programming language (C or C++).");
    printf("    %-28s %s\n", "--type <binary|library>", "Specifies the main type of project (executable or library).");
    printf("    %-28s %s\n", "--build-system <make|cmake>", "Chooses the build system (Makefile or CMake).");
    printf("    %-28s %s\n", "--output-dir <directory>", "Specifies the output directory for the project.\n");
    printf("  %-30s %s\n", "protogen add <binary|library|test>", "Adds a new component to the project.");
    printf("    %-28s %s\n", "--name <component-name>", "Name of the component to be added.");
    printf("    %-28s %s\n", "--src-dir <directory>", "Specifies the source directory for the new component.");
    printf("    %-28s %s\n", "--include-dir <directory>", "Specifies the include directory for the new component.\n");
    printf("  %-30s %s\n", "protogen --version", "Displays version information.");
    printf("\n");
}

// Function to print usage information for the 'init' command
void print_init_usage() {
    printf("Usage: protogen init <project-name> [options]\n");
    printf("Initializes a new C or C++ project with the specified name.\n\n");
    printf("Options:\n");
    printf("  %-28s %s (default: %s)\n", "--lang <c|cpp>", "Specifies the programming language (C or C++).", "c");
    printf("  %-28s %s (default: %s)\n", "--type <binary|library>", "Specifies the main type of project (executable or library).", "binary");
    printf("  %-28s %s (default: %s)\n", "--build-system <make|cmake>", "Chooses the build system (make or cmake).", "make");
    printf("  %-28s %s (default: %s)\n", "--output-dir <directory>", "Specifies the output directory for the project.", "./");
    printf("\n");
}

// Function to print usage information for the 'add' command
void print_add_usage() {
    printf("Usage: protogen add <binary|library|test> --name <name> [options]\n");
    printf("Options:\n");
    printf("  %-28s %s\n", "--name <component-name>", "Name of the component to be added.");
    printf("  %-28s %s\n", "--src-dir <directory>", "Specifies the source directory for the new component.");
    printf("  %-28s %s\n", "--include-dir <directory>", "Specifies the include directory for the new component.");
    printf("\n");
}

// Function to handle the 'init' command
void handle_init(int argc, char *argv[]) {
    const char *project_name = NULL;
    const char *lang = "c";
    const char *type = "binary";
    const char *build_system = "make";
    const char *output_dir = "./";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--lang") == 0 && i + 1 < argc) {
            lang = argv[++i];
        } else if (strcmp(argv[i], "--type") == 0 && i + 1 < argc) {
            type = argv[++i];
        } else if (strcmp(argv[i], "--build-system") == 0 && i + 1 < argc) {
            build_system = argv[++i];
        } else if (strcmp(argv[i], "--output-dir") == 0 && i + 1 < argc) {
            output_dir = argv[++i];
        } else if (!project_name) {
            project_name = argv[i];
        } else {
            print_init_usage();
            return;
        }
    }

    if (!project_name || !lang || !type || !build_system) {
        printf("Missing required options for 'init' command.\n");
        print_init_usage();
        return;
    }

    printf("Initializing project '%s'...\n", project_name);
    printf("Language: %s\n", lang);
    printf("Type: %s\n", type);
    printf("Build System: %s\n", build_system);
    printf("Output Directory: %s\n", output_dir);

    initialize_project(project_name, lang, type, build_system, output_dir);
}

// Function to handle the 'add' command
void handle_add(int argc, char *argv[]) {
    const char *component = NULL;
    const char *name = NULL;
    const char *src_dir = NULL;
    const char *include_dir = NULL;

    if (argc > 1) {
        component = argv[1];
    }

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--name") == 0 && i + 1 < argc) {
            name = argv[++i];
        } else if (strcmp(argv[i], "--src-dir") == 0 && i + 1 < argc) {
            src_dir = argv[++i];
        } else if (strcmp(argv[i], "--include-dir") == 0 && i + 1 < argc) {
            include_dir = argv[++i];
        } else {
            printf("Unknown option: %s\n", argv[i]);
            print_add_usage();
            return;
        }
    }

    if (!component || !name) {
        print_add_usage();
        return;
    }

    // Set default values if not provided
    if (!src_dir) {
        src_dir = name;
    }

    printf("Adding component '%s'...\n", name);
    printf("Component Type: %s\n", component);
    printf("Source Directory: %s\n", src_dir);
    if (include_dir) {
        printf("Include Directory: %s\n", include_dir);
    }

    // Call to a function that will actually add the component (to be implemented)
}

// Function to handle the '--version' command
void handle_version() {
    printf("ProtoGen version 1.0.0\n");
}
