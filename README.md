# Simple C Shell

A minimal Unix-like shell written in C for learning low-level system concepts such as process creation, argument parsing, and memory management.

## Features

- Command execution using `fork()` and `execvp()`
- Built-in commands:
  - `cd`
  - `exit`

- Dynamic argument parsing (vector-based)
- Custom input reader (no `fgets`)
- Modular structure (input, parser, process, utils)

## Project Structure

```
.
├── include/
│   ├── common.h
│   ├── input.h
│   ├── parser.h
│   ├── process.h
│   └── utils.h
├── src/
│   ├── input.c
│   ├── parser.c
│   ├── process.c
│   ├── utils.c
│   └── main.c
├── TODO.md
└── README.md
```

## Build

Compile all source files:

```bash
gcc -Wall -Wextra -Werror src/*.c -Iinclude -o myshell
```

## Run

```bash
./myshell
```

## How It Works

1. Display prompt (current working directory)
2. Read user input
3. Parse input into arguments
4. Execute:
   - Built-in command (`cd`, `exit`)
   - or external program via `execvp`

5. Repeat

## Notes

- Argument parsing is space-based (no quotes or escaping yet)
- Arguments are stored as `char*` and depend on the input buffer lifetime
- Designed for learning purposes, not production use

## TODO

See `TODO.md` for planned features:

- Pipes (`|`)
- Output redirection (`>`, `>>`)
- Input redirection (`<`)
- Better parsing (quotes, escaping)
