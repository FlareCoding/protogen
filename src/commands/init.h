#ifndef INIT_H
#define INIT_H

// Function to initialize a new project
void initialize_project(
    const char *project_name,
    const char *lang,
    const char *type,
    const char *build_system,
    const char *output_dir
);

// Helper functions (internal use)
void create_directories(
    const char *project_name,
    const char *output_dir
);

void create_files(
    const char *project_name,
    const char *lang,
    const char *type,
    const char *build_system,
    const char *output_dir
);

void generate_main_source_file(
    const char *project_name,
    const char *lang,
    const char *output_dir
);

#endif // INIT_H
