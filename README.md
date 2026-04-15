# minishell

A small Unix shell written in C.

## Features

- Interactive prompt
- Command parsing (quotes, pipes, redirections)
- Environment variable expansion
- Built-in commands (e.g. `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
- Executes external programs via `PATH`

> Note: Exact feature set depends on the current implementation in this repository.

## Requirements

- A POSIX-compatible system (Linux/macOS)
- `make`
- A C toolchain (`cc`/`clang`/`gcc`)

## Build

```sh
make
```

This should produce the `minishell` executable.

## Run

```sh
./minishell
```

## Cleaning

```sh
make clean      # remove object files
make fclean     # remove objects + executable
make re         # full rebuild
```

## Project structure (typical)

Common directories/files you may find in a minishell project:

- `src/` — source files
- `include/` — headers
- `libft/` — local utility library (if present)
- `Makefile`

## Contributing

1. Create a feature branch
2. Make your changes
3. Open a pull request

## License

If this project is part of a school assignment, distribution may be restricted. Otherwise, add a LICENSE file to clarify reuse.