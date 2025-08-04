# 🐚 Minishell - 42 School Project

> As beautiful as a shell

A simple UNIX shell implementation built in C, recreating basic bash functionality including command parsing, execution, pipes, redirections, and built-in commands.

## 📋 Project Overview

This project involves creating a functional shell that can:
- Parse and execute commands
- Handle quotes and environment variables
- Implement pipes and redirections
- Support built-in commands
- Manage signals properly

## 👥 Team Members

- **Developer A (Parser)**: Input processing, tokenization, quote handling
- **Developer B (Executor)**: Process management, built-ins, pipes

## 🚀 Progress Tracker

### ✅ Day 1 - Foundation & Setup
**Research completed:**
- [x] Documented bash quote behavior
- [x] Tested redirection scenarios  
- [x] Analyzed pipe behavior
- [x] Recorded environment variable expansion
- [ ] Noted edge cases and errors

**Project setup completed:**
- [x] Git repository initialized
- [x] Directory structure created
- [x] Makefile working
- [x] Header file with data structures
- [x] Main function with shell loop
- [x] Stub functions compile and run

**Coordination with partner:**
- [x] Shared the `minishell.h` file
- [ ] Agreed on data structure interfaces

### 🔄 Day 2 - Basic Implementation (In Progress)
**Parser Development (Developer A):**
- [x]Implement basic tokenizer
- [x] Handle simple quotes
- [x] Environment variable expansion
- [x] Basic command parsing

**Executor Development (Developer B):**
- [x] Basic command execution
- [ ] Fork/exec implementation
- [x]imple built-ins (echo, pwd)
- [x] Basic error handling

### 📅 Week 1 Goals
- [x] Basic shell loop functional
- [ ] Simple command execution (Partial)
- [ ] Quote handling
- [ ] Basic redirections
- [ ] Environment variables (partial)

### 📅 Week 2 Goals  
- [ ] Pipe implementation
- [ ] All built-in commands
- [ ] Signal handling
- [ ] Complex parsing scenarios

### 📅 Week 3 Goals
- [ ] Integration testing
- [ ] Memory leak fixes
- [ ] Edge case handling
- [ ] Evaluation preparation

## 🏗️ Project Structure

```
minishell/
├── 📁 include/
│   └── minishell.h              # Main header file with all structures
├── 📁 src/
│   ├── main.c                   # Main shell loop and initialization
│   ├── utils.c                  # Utility functions (strdup, strjoin, etc.)
│   ├── 📁 parsing/
│   │   ├── lexer.c              # Tokenization and lexical analysis
│   │   ├── parser.c             # Command parsing and syntax analysis
│   │   ├── quotes.c             # Quote handling and validation
│   │   └── expander.c           # Variable expansion ($VAR, $?)
│   ├── 📁 execution/
│   │   ├── executor.c           # Command execution and process management
│   │   ├── pipes.c              # Pipe implementation and management
│   │   └── redirections.c       # File redirection handling
│   └── 📁 builtins/
│       ├── echo.c               # echo command implementation
│       ├── cd.c                 # cd command implementation
│       ├── pwd.c                # pwd command implementation
│       ├── export.c             # export command implementation
│       ├── unset.c              # unset command implementation
│       ├── env.c                # env command implementation
│       └── exit.c               # exit command implementation
├── 📁 tests/
│   ├── 📁 unit/
│   │   ├── test_lexer.c         # Lexer unit tests
│   │   ├── test_parser.c        # Parser unit tests
│   │   └── test_quotes.c        # Quote handling tests
│   └── 📁 integration/
│       ├── test_commands.sh     # Command execution tests
│       ├── test_pipes.sh        # Pipe functionality tests
│       └── test_redirections.sh # Redirection tests
├── 📁 docs/
│   ├── bash_behavior_notes.txt  # Research notes on bash behavior
│   ├── development_log.md       # Daily development progress
│   └── coding_standards.md      # Team coding conventions
├── Makefile                     # Build system
├── README.md                    # This file
└── .gitignore                   # Git ignore rules
```