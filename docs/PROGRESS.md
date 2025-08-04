# Minishell Development Progress

## Project Overview
Building a simple shell (like bash) in C that handles basic command execution, parsing, and signal management.

## Current Project Structure
```
minishell/
├── Makefile
├── src/
│   ├── main.c          # Main program loop and signal handling
│   ├── prompt.c        # Prompt display and user input
│   ├── parser.c        # Command parsing and tokenization
│   └── executor.c      # Command execution and PATH resolution
├── includes/
│   └── minishell.h     # Header with structures and function prototypes
└── obj/                # Object files (created automatically)
```

---

## ✅ Step 1: Basic Shell Foundation
**Goal**: Create a working shell prompt with proper signal handling

### Features Implemented
- **Interactive prompt**: Shows `minishell$ ` and waits for input
- **Command history**: Using readline library for up/down arrow navigation
- **Signal handling**:
  - `Ctrl+C`: Displays new prompt on new line
  - `Ctrl+D`: Exits the shell gracefully
  - `Ctrl+\`: Does nothing (ignored completely)
- **Memory management**: Proper cleanup with `rl_clear_history()`
- **Exit command**: Type `exit` to quit

### Key Components
- **Global variable**: `g_signal` (only one allowed by subject)
- **Signal handlers**: Using `sigaction()` for proper signal management
- **Readline integration**: For interactive input and history

### Test Commands
```bash
# Compile and run
make
./minishell

# Test signals
minishell$ [Ctrl+C]   # Should show new prompt
minishell$ [Ctrl+\]   # Should do nothing  
minishell$ [Ctrl+D]   # Should exit
minishell$ exit       # Should exit
```

---

## ✅ Step 2: Command Parsing & Execution
**Goal**: Parse user input and execute basic commands

### Features Implemented
- **Command parsing**: Splits input into command and arguments
- **PATH resolution**: Finds executables in system PATH
- **Process management**: Uses `fork()` and `execve()` for command execution
- **Error handling**: Shows "command not found" for invalid commands
- **Absolute/relative paths**: Handles commands with `/` in them

### Key Components
- **Command structure**: `t_cmd` with args array and argc count
- **Parser functions**: 
  - `split_input()`: Tokenizes input by spaces/tabs
  - `parse_command()`: Creates command structure
  - `free_command()`: Cleans up memory
- **Executor functions**:
  - `find_command_path()`: Searches PATH for executables
  - `execute_command()`: Forks and executes commands

### Test Commands
```bash
# Basic commands
minishell$ ls
minishell$ ls -la
minishell$ pwd
minishell$ echo hello world
minishell$ whoami
minishell$ date

# Absolute paths
minishell$ /bin/ls
minishell$ /usr/bin/whoami

# Error handling
minishell$ nonexistent_command
# Should show: minishell: nonexistent_command: command not found
```

---

## Current Capabilities

### ✅ What Works
- [x] Display interactive prompt
- [x] Read user input with history
- [x] Handle Ctrl+C, Ctrl+D, Ctrl+\ signals correctly  
- [x] Parse simple commands (space-separated arguments)
- [x] Execute commands found in PATH
- [x] Execute commands with absolute/relative paths
- [x] Show error messages for invalid commands
- [x] Proper memory management (no leaks except readline)
- [x] Exit gracefully with `exit` command

### ⏳ Not Yet Implemented
- [ ] Built-in commands (cd, pwd, echo, export, unset, env, exit)
- [ ] Quote handling (single `'` and double `"` quotes)
- [ ] Environment variable expansion (`$VAR`, `$?`)
- [ ] Redirections (`<`, `>`, `<<`, `>>`)
- [ ] Pipes (`|`)
- [ ] Advanced parsing (handle special characters)

---

## Technical Details

### Memory Management
- All dynamically allocated memory is properly freed
- Command structures cleaned up after execution
- Readline history cleared on exit
- No memory leaks in our code (readline may have some, which is allowed)

### Signal Handling
- Uses `sigaction()` instead of deprecated `signal()`
- SIGINT (Ctrl+C): Custom handler for new prompt
- SIGQUIT (Ctrl+\): Completely ignored with `SIG_IGN`
- Only one global variable `g_signal` used (subject requirement)

### Process Management
- Parent process forks for each command
- Child process uses `execve()` to replace itself with command
- Parent waits for child completion with `waitpid()`
- Proper exit status handling

---

## Next Steps

### Step 3: Built-in Commands (Planned)
Implement shell built-ins that run in the main process:
- `cd` - Change directory
- `pwd` - Print working directory  
- `echo` - Print arguments (with -n option)
- `export` - Set environment variables
- `unset` - Remove environment variables
- `env` - Display environment variables
- `exit` - Exit shell

### Step 4: Quote Handling (Planned)
- Single quotes: Prevent all interpretation
- Double quotes: Allow `$` expansion only

### Step 5: Redirections & Pipes (Planned)
- Input/output redirection
- Here-documents
- Pipe chains

---

## Compilation & Usage

```bash
# Compile
make

# Clean and recompile
make re

# Run
./minishell

# Clean up
make fclean
```

### Dependencies
- `libreadline-dev` (Ubuntu/Debian) or `readline` (macOS)
- Standard C library
- POSIX-compliant system

---

## Files Overview

| File | Purpose | Key Functions |
|------|---------|---------------|
| `main.c` | Entry point, signal handling, main loop | `main()`, `shell_loop()`, signal handlers |
| `prompt.c` | User input handling | `read_input()`, `display_prompt()` |
| `parser.c` | Command parsing and tokenization | `parse_command()`, `split_input()` |
| `executor.c` | Command execution and PATH resolution | `execute_command()`, `find_command_path()` |
| `minishell.h` | Header with all prototypes and structures | Structures, function prototypes |

**Status**: ✅ Step 1 & 2 Complete - Basic shell with command execution working!