# Minishell Development Progress

## Project Overview
Building a simple shell (like bash) in C that handles basic command execution, parsing, signal management, and built-in commands.

## Current Project Structure
```
minishell/
├── Makefile
├── src/
│   ├── main.c          # Main program loop and signal handling
│   ├── prompt.c        # Prompt display and user input
│   ├── parser.c        # Command parsing and tokenization
│   ├── executor.c      # Command execution and PATH resolution
│   └── builtins.c      # Built-in commands implementation
├── includes/
│   └── minishell.h     # Header with structures and function prototypes
└── obj/                # Object files (created automatically)
```

---

## ✅ Step 4: Quote Handling & Variable Expansion
**Goal**: Implement advanced parsing with quotes and environment variable expansion

### Features Implemented
- **Single quote handling**: `'text'` prevents all interpretation (literal strings)
- **Double quote handling**: `"text with $VAR"` allows variable expansion only
- **Environment variable expansion**: `$VAR` expands to environment variable values
- **Exit status variable**: `$?` expands to last command's exit status
- **Quote removal**: Properly removes quotes after processing content
- **Exit status tracking**: Updates global variable after each command execution

### Key Components
- **Quote parser**: `handle_quotes()` processes different quote types
- **Variable expander**: `expand_variables()` handles `$VAR` and `$?` expansion
- **Exit status tracking**: `g_last_exit_status` global variable
- **Enhanced tokenizer**: Updated `split_input()` to handle quotes and variables
- **Quote finder**: `find_closing_quote()` locates matching quote pairs

### Test Commands
```bash
# Variable expansion
minishell$ export TEST_VAR=hello
minishell$ echo $TEST_VAR
hello

# Exit status testing
minishell$ ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
minishell$ echo $?
2
minishell$ echo success
success
minishell$ echo $?
0

# Single quotes (no expansion)
minishell$ echo '$TEST_VAR and $?'
$TEST_VAR and $?

# Double quotes (with expansion)
minishell$ echo "Hello $TEST_VAR, exit: $?"
Hello hello, exit: 0

# Mixed usage
minishell$ echo 'literal: $TEST_VAR' and "expanded: $TEST_VAR"
literal: $TEST_VAR and expanded: hello
```

---

## ✅ Step 3: Built-in Commands
**Goal**: Implement shell built-in commands that run in the main process

### Features Implemented
- **Built-in detection**: Checks for built-ins before external commands
- **No forking for built-ins**: Built-ins run directly in shell process
- **State modification**: Commands like `cd` and `export` can change shell state
- **All required built-ins**: Complete implementation of 7 mandatory built-ins

### Built-in Commands Implemented
- **`echo [-n] [args...]`**: Print arguments with optional newline suppression
- **`cd [directory]`**: Change working directory (supports relative/absolute paths + HOME)
- **`pwd`**: Print current working directory
- **`export VAR=value`**: Set environment variables
- **`unset VAR`**: Remove environment variables
- **`env`**: Display all environment variables
- **`exit [code]`**: Exit shell with optional status code

### Key Components
- **Built-in dispatcher**: `is_builtin()` and `execute_builtin()` functions
- **Individual implementations**: Each built-in as separate function
- **Error handling**: Proper error messages for invalid usage
- **Environment manipulation**: `setenv()` and `unsetenv()` integration

### Test Commands
```bash
# Echo tests
minishell$ echo Hello World
Hello World
minishell$ echo -n No newline
No newlineminishell$ 

# Directory navigation
minishell$ pwd
/home/user/current/dir
minishell$ cd /tmp
minishell$ pwd
/tmp
minishell$ cd
minishell$ pwd
/home/user

# Environment variables
minishell$ export MY_VAR=hello
minishell$ env | grep MY_VAR
MY_VAR=hello
minishell$ unset MY_VAR
minishell$ env | grep MY_VAR
[nothing shown]

# Exit
minishell$ exit 42
exit
[shell exits with code 42]
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
- [x] Parse commands with space-separated arguments
- [x] Execute commands found in PATH
- [x] Execute commands with absolute/relative paths
- [x] Show error messages for invalid commands
- [x] **Built-in commands: echo, cd, pwd, export, unset, env, exit**
- [x] **Environment variable manipulation**
- [x] **Directory navigation without forking**
- [x] **Single quote handling (literal strings)**
- [x] **Double quote handling (with variable expansion)**
- [x] **Environment variable expansion ($VAR)**
- [x] **Exit status variable ($?)**
- [x] **Quote removal after processing**
- [x] Proper memory management (no leaks except readline)
- [x] Exit gracefully with `exit` command and status codes

### ⏳ Not Yet Implemented
- [ ] Redirections (`<`, `>`, `<<`, `>>`)
- [ ] Pipes (`|`)
- [ ] Advanced parsing (handle special characters like `;`, `\`)

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
- **External commands**: Parent process forks for each command
- **Built-in commands**: Execute directly in main shell process (no fork)
- Child process uses `execve()` to replace itself with command
- Parent waits for child completion with `waitpid()`
- Proper exit status handling

### Built-in Architecture
- **Detection first**: Check if command is built-in before PATH lookup
- **Centralized dispatcher**: Single entry point routing to specific implementations
- **State preservation**: Built-ins can modify shell environment and working directory
- **Error consistency**: All built-ins follow similar error reporting patterns

### Quote and Variable Processing
- **Quote parsing**: Handles single and double quotes with proper nesting
- **Variable expansion**: Supports environment variables and exit status
- **Memory efficient**: Dynamic allocation with proper cleanup
- **Context-aware**: Different behavior inside different quote types
- **Error resilient**: Handles unclosed quotes gracefully

---

## Next Steps

### Step 4: Quote Handling & Variable Expansion (Planned)
Implement advanced parsing features:
- Single quotes: Prevent all interpretation (`'literal string'`)
- Double quotes: Allow `# Minishell Development Progress

## Project Overview
Building a simple shell (like bash) in C that handles basic command execution, parsing, signal management, and built-in commands.

## Current Project Structure
```
minishell/
├── Makefile
├── src/
│   ├── main.c          # Main program loop and signal handling
│   ├── prompt.c        # Prompt display and user input
│   ├── parser.c        # Command parsing and tokenization
│   ├── executor.c      # Command execution and PATH resolution
│   └── builtins.c      # Built-in commands implementation
├── includes/
│   └── minishell.h     # Header with structures and function prototypes
└── obj/                # Object files (created automatically)
```

---

## ✅ Step 3: Built-in Commands
**Goal**: Implement shell built-in commands that run in the main process

### Features Implemented
- **Built-in detection**: Checks for built-ins before external commands
- **No forking for built-ins**: Built-ins run directly in shell process
- **State modification**: Commands like `cd` and `export` can change shell state
- **All required built-ins**: Complete implementation of 7 mandatory built-ins

### Built-in Commands Implemented
- **`echo [-n] [args...]`**: Print arguments with optional newline suppression
- **`cd [directory]`**: Change working directory (supports relative/absolute paths + HOME)
- **`pwd`**: Print current working directory
- **`export VAR=value`**: Set environment variables
- **`unset VAR`**: Remove environment variables
- **`env`**: Display all environment variables
- **`exit [code]`**: Exit shell with optional status code

### Key Components
- **Built-in dispatcher**: `is_builtin()` and `execute_builtin()` functions
- **Individual implementations**: Each built-in as separate function
- **Error handling**: Proper error messages for invalid usage
- **Environment manipulation**: `setenv()` and `unsetenv()` integration

### Test Commands
```bash
# Echo tests
minishell$ echo Hello World
Hello World
minishell$ echo -n No newline
No newlineminishell$ 

# Directory navigation
minishell$ pwd
/home/user/current/dir
minishell$ cd /tmp
minishell$ pwd
/tmp
minishell$ cd
minishell$ pwd
/home/user

# Environment variables
minishell$ export MY_VAR=hello
minishell$ env | grep MY_VAR
MY_VAR=hello
minishell$ unset MY_VAR
minishell$ env | grep MY_VAR
[nothing shown]

# Exit
minishell$ exit 42
exit
[shell exits with code 42]
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
- [x] **Built-in commands: echo, cd, pwd, export, unset, env, exit**
- [x] **Environment variable manipulation**
- [x] **Directory navigation without forking**
- [x] Proper memory management (no leaks except readline)
- [x] Exit gracefully with `exit` command and status codes

### ⏳ Not Yet Implemented
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
- **External commands**: Parent process forks for each command
- **Built-in commands**: Execute directly in main shell process (no fork)
- Child process uses `execve()` to replace itself with command
- Parent waits for child completion with `waitpid()`
- Proper exit status handling

### Built-in Architecture
- **Detection first**: Check if command is built-in before PATH lookup
- **Centralized dispatcher**: Single entry point routing to specific implementations
- **State preservation**: Built-ins can modify shell environment and working directory
- **Error consistency**: All built-ins follow similar error reporting patterns

---

 expansion only (`"Hello $USER"`)
- Environment variables: `$VAR` expansion
- Exit status variable: `$?` expansion

### Step 5: Redirections (Planned)
- Input redirection: `<`
- Output redirection: `>`  
- Here-documents: `<<`
- Append redirection: `>>`

### Step 6: Pipes (Planned)
- Simple pipes: `command1 | command2`
- Multiple pipes: `cmd1 | cmd2 | cmd3`
- Proper file descriptor management

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
| `builtins.c` | Built-in commands implementation | `is_builtin()`, `builtin_*()` functions |
| `minishell.h` | Header with all prototypes and structures | Structures, function prototypes |

**Status**: ✅ Step 1, 2, 3 & 4 Complete - Advanced shell with quotes and variables working!