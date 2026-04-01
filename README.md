# Shell

A small Unix-like shell written in C.

This project is a learning build focused on understanding how a shell actually works at the systems level: reading input, parsing commands, handling built-in commands, creating child processes, executing programs, and waiting for them to finish.

## Current Features

- Interactive prompt
- Reads user input with `fgets`
- Parses arguments by spaces
- Runs external commands with `fork()`, `execvp()`, and `waitpid()`
- Built-in `cd`
- Built-in `exit`
- Shows the current working directory in the prompt

## Project Goal

The goal of this project is not to build a full Bash replacement.

It is to learn the core ideas behind shells by implementing them step by step in plain C.

## Tech

- C
- POSIX system calls
- GCC or Clang
- Linux / Unix-like environment

## Build

```bash
gcc -Wall -Wextra -Werror -pedantic -std=c11 main.c -o myshell
```
