# ProtoGen

ProtoGen is a command-line tool designed to simplify the setup of C and C++ projects. It provides a straightforward way to generate project templates, manage components, and integrate build systems like Makefile and CMake. With ProtoGen, developers can quickly scaffold their projects and focus on coding rather than configuration.

## Table of Contents

1. [Usage](#usage)
2. [Examples](#examples)
3. [Installation](#installation)
4. [Contributions](#contributions)
5. [License](#license)

## Usage

ProtoGen provides a simple set of commands to initialize projects, add components, and manage configurations. Below is a table summarizing the available commands and their options.

| Command                       | Options                                                             | Description                                     |
|-------------------------------|---------------------------------------------------------------------|-------------------------------------------------|
| `protogen --help`             | -                                                                   | Displays help information.                      |
| `protogen init <project-name>`| `--lang <c\|cpp>`<br>`--type <binary\|library>`<br>`--build-system <make\|cmake>`<br>`--output-dir <directory>` | Initializes a new project. |
| `protogen add <binary\|library\|test>` | `--name <component-name>`<br>`--src-dir <directory>`<br>`--include-dir <directory>` | Adds a new component to the project. |
| `protogen --version`          | -                                                                   | Displays version information.                   |

### Command Descriptions

- `protogen --help`: Displays a list of available commands and general usage information.
- `protogen init <project-name>`: Initializes a new project with the specified name, programming language, and main component type.
  - `--lang <c|cpp>`: Specifies the programming language (C or C++).
  - `--type <binary|library>`: Specifies the main type of project (executable or library).
  - `--build-system <make|cmake>`: Chooses the build system (Makefile or CMake).
  - `--output-dir <directory>`: Specifies the output directory for the project (default: current directory).
- `protogen add <binary|library|test>`: Adds a new component to the existing project.
  - `--name <component-name>`: Name of the component to be added.
  - `--src-dir <directory>`: Specifies the source directory for the new component.
  - `--include-dir <directory>`: Specifies the include directory for the new component.
- `protogen --version`: Displays the version number of ProtoGen.

## Examples

Here are a few example command-line usages of ProtoGen for different scenarios:

### 1. Initialize a New C++ Project with CMake

Create a new C++ project named `MyApp`, set up as an executable with CMake as the build system, and output to the `projects` directory:

```bash
protogen init MyApp --lang cpp --type binary --build-system cmake --output-dir ./projects
```

### 2. Initialize a New C Library Project with Makefile

Create a new C project named MyLibrary, set up as a library with a Makefile for the build system, and place it in the current directory:

```bash
protogen init MyLibrary --lang c --type library --build-system make
```

### 3. Add a Library Component to an Existing Project

Add a new library component named Logger to an existing project, specifying the source and include directories:

```bash
protogen add library --name Logger --src-dir src/logger --include-dir include/logger
```

### 4. Add a Test Component to an Existing Project
Add a new test component named UnitTests to an existing project:

```bash
protogen add test --name UnitTests --src-dir tests
```

## Installation

To install ProtoGen, clone the repository and run the installation script. This will build the executable and place it in your path.

```bash
git clone https://github.com/your-username/protogen.git
cd protogen
./install.sh
```

## Contributions

Contributions are welcome! If you'd like to contribute, please fork the repository and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

