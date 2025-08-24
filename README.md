# Minishell - As Beautiful as a Shell

A simple shell implementation written in C, recreating basic bash functionality as part of the 42 School curriculum.

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Implementation Details](#implementation-details)
- [Memory Management](#memory-management)
- [Signal Handling](#signal-handling)
- [Contributing](#contributing)

## 🔍 About

Minishell is a simplified shell implementation that mimics the behavior of bash. This project helps understand:
- Process creation and management
- File descriptors and I/O redirection
- Signal handling
- Parsing and tokenization
- Memory management in C

## ✨ Features

### Core Functionality
- **Interactive command line** with prompt display
- **Command history** using readline library
- **Executable search** via PATH variable or absolute/relative paths
- **Environment variables** expansion (`$VAR`, `$?`)
- **Quote handling** (single and double quotes)

### I/O Redirection
- `<` Input redirection
- `>` Output redirection  
- `<<` Here document (heredoc)
- `>>` Append mode

### Advanced Features
- **Pipes** (`|`) for command chaining
- **Logical operators** (`&&`, `||`) with parentheses support (bonus)
- **Wildcard expansion** (`*`) for current directory (bonus)
- **Signal handling** (Ctrl-C, Ctrl-D, Ctrl-\)

### Built-in Commands
- `echo` (with `-n` option)
- `cd` (relative/absolute paths)
- `pwd`
- `export`
- `unset` 
- `env`
- `exit`

## 🚀 Installation

### Prerequisites
- GCC compiler
- Make
- Readline library

### Building
```bash
git clone <repository-url>
cd minishell
make
```

### Cleaning
```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild everything
```

## 💻 Usage

### Starting the Shell
```bash
./minishell
```

### Example Commands
```bash
minishell$ echo "Hello World"
Hello World

minishell$ ls -la | grep minishell
# Lists files containing 'minishell'

minishell$ export MY_VAR="test"
minishell$ echo $MY_VAR
test

minishell$ cat << EOF
> This is a heredoc
> EOF
This is a heredoc

minishell$ ls *.c > source_files.txt
# Redirects output to file
```

## 🛠 Built-in Commands

| Command | Description | Usage |
|---------|-------------|--------|
| `echo` | Display text | `echo [-n] [text...]` |
| `cd` | Change directory | `cd [path]` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variable | `export [VAR=value]` |
| `unset` | Remove environment variable | `unset [VAR]` |
| `env` | Display environment | `env` |
| `exit` | Exit shell | `exit [code]` |

## 🏗 Architecture

The project follows a modular architecture:

### Core Components

1. **Tokenizer** (`tokenizing/`)
   - Lexical analysis of input
   - Quote handling
   - Token classification

2. **Parser** (`parsing/`)
   - Syntax analysis
   - Abstract Syntax Tree (AST) construction
   - Error handling

3. **Expander** (`expander/`)
   - Variable expansion (`$VAR`, `$?`)
   - Quote removal
   - Wildcard expansion
   - Word splitting

4. **Executor** (`exec/`)
   - Command execution
   - Process management
   - I/O redirection
   - Pipeline handling

5. **Built-ins** (`builtins/`)
   - Implementation of shell built-in commands

## 📁 Project Structure

```
minishell/
├── Makefile
├── include/
│   ├── minishell.h
│   ├── parsing.h
│   └── tokenizing.h
├── libraries/
│   └── libft/              # Custom C library
├── builtins/               # Built-in commands
├── cleaning/               # Memory management
├── exec/                   # Command execution
├── expander/               # Variable/wildcard expansion
├── parsing/                # Syntax analysis
├── tokenizing/             # Lexical analysis
└── main.c                  # Entry point
```

## 🔧 Implementation Details

### Tokenization Process
1. **Lexical Analysis**: Input string is broken into tokens
2. **Quote Handling**: Proper parsing of quoted strings
3. **Operator Recognition**: Identification of pipes, redirections, logical operators

### Parsing Strategy
- **Recursive Descent Parser**: Builds AST from tokens
- **Operator Precedence**: Handles `&&`, `||`, and `|` with correct precedence
- **Error Recovery**: Syntax error detection and reporting

### Execution Model
- **Process Creation**: Fork/exec model for external commands
- **Pipeline Implementation**: Pipe creation and file descriptor management
- **Signal Management**: Proper handling of interactive signals

### Memory Management
- **Garbage Collection**: Custom garbage collector for memory tracking
- **Leak Prevention**: Systematic cleanup of all allocated resources
- **Error Handling**: Graceful handling of allocation failures

## 🧠 Memory Management

The project implements a custom garbage collection system:

```c
// Add pointer to garbage collection
ptr = ft_garbage_collector(malloc(size), false);

// Clean all collected memory
ft_garbage_collector(NULL, true);
```

This ensures no memory leaks while maintaining clean code structure.

## 📡 Signal Handling

Interactive mode signal behavior:
- **Ctrl-C**: Displays new prompt on new line
- **Ctrl-D**: Exits the shell
- **Ctrl-\**: Does nothing (ignored)

The implementation uses a single global variable to track signal states, following 42 School requirements.

## 🔒 Error Handling

Comprehensive error handling for:
- **Syntax errors**: Malformed commands
- **Permission errors**: File access issues  
- **Command not found**: Invalid executables
- **Memory allocation**: Out of memory conditions
- **System call failures**: Fork, pipe, exec errors

## 🧪 Testing

The shell has been tested against bash behavior for:
- Basic command execution
- Complex pipeline chains
- Quote handling edge cases
- Environment variable expansion
- Signal handling scenarios
- Memory leak detection

## 📝 Notes

- The `readline()` function may cause memory leaks that are not fixed (as per project requirements)
- Only one global variable is used for signal handling
- The shell follows bash behavior as the reference implementation
- Bonus features (logical operators, wildcards) are only evaluated if the mandatory part is perfect

## 🏆 Project Requirements

- ✅ Written in C following 42 Norm
- ✅ No memory leaks (except readline)
- ✅ Proper error handling
- ✅ Makefile with required rules
- ✅ Uses only allowed external functions
- ✅ Signal handling compliance
- ✅ Interactive shell behavior

## 📚 Learning Outcomes

This project teaches:
- **System Programming**: Process management, file descriptors
- **Parsing Techniques**: Lexical analysis, syntax trees
- **Memory Management**: Custom allocators, leak prevention  
- **Signal Processing**: Unix signal handling
- **Shell Internals**: Understanding how shells work

---

*"Thanks to Minishell, you'll be able to travel through time and come back to problems people faced when Windows didn't exist."*
