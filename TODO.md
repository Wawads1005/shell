# myshell TODO

## Core Rules

- Build one feature at a time
- Do NOT jump ahead
- Do NOT overengineer
- Keep everything in one file until stable

---

## Phase 0 — Setup

- [x] Create main.c
- [x] Compile with:
      gcc -Wall -Wextra -Werror -pedantic -std=c11 main.c -o myshell
- [x] Program runs

---

## Phase 1 — REPL

- [x] Print prompt: myshell>
- [x] Read input (fgets)
- [x] Handle EOF (Ctrl+D)
- [x] Remove newline
- [] Ignore empty input
- [x] Loop forever

DONE WHEN:

- You can type anything and it doesn't crash

---

## Phase 2 — Parse

- [x] Split input by spaces
- [x] Store in char \*arguments[]
- [x] Last element = NULL

DONE WHEN:

- "ls -la" becomes ["ls", "-la", NULL]

---

## Phase 3 — exit

- [x] Detect "exit"
- [x] Break loop

DONE WHEN:

- myshell exits cleanly

---

## Phase 4 — Execute

- [x] fork()
- [x] child → execvp()
- [x] parent → waitpid()
- [x] perror() on failure

TEST:

- [x] ls
- [x] pwd
- [x] echo hello
- [x] invalid command

DONE WHEN:

- You can run real commands

---

## Phase 5 — cd

- [x] Detect "cd"
- [x] Use chdir()
- [x] Handle missing/invalid path

IMPORTANT:

- Do NOT use fork()

DONE WHEN:

- cd actually changes directory

---

## Phase 6 — Stability

- [x] Check fork() result
- [x] Check execvp() result
- [ ] Check waitpid() result
- [ ] Check chdir() result
- [x] Handle empty arguments[0]

DONE WHEN:

- No crashes on bad input

---

## Phase 7 — Clean Up

- [x] Extract functions
- [x] Clean main()
- [x] Use constants for sizes

DONE WHEN:

- Code is readable

---

## Phase 8 — Output Redirection >

- [ ] Detect ">"
- [ ] Get filename
- [ ] open() file
- [ ] dup2() to stdout
- [ ] Remove tokens before exec

TEST:

- [ ] echo hello > file.txt

---

## Phase 9 — Input Redirection <

- [ ] Detect "<"
- [ ] open() file
- [ ] dup2() to stdin

TEST:

- [ ] wc -l < file.txt

---

## Phase 10 — Pipe |

- [ ] Detect "|"
- [ ] pipe()
- [ ] fork left process
- [ ] fork right process
- [ ] connect via dup2()
- [ ] close unused fds

TEST:

- [ ] ls | wc -l

---

## Phase 11 — Multiple Pipes

- [ ] Support chaining

TEST:

- [ ] cat file | grep x | wc -l

---

## Optional

- [ ] Show current directory in prompt
- [ ] cd with no args → home
- [ ] background jobs (&)
- [ ] simple quotes support

---

## Milestone

Working shell:

- [ ] ls
- [ ] pwd
- [ ] echo hello
- [ ] cd ..
- [ ] exit

IF THIS WORKS → YOU BUILT A REAL SHELL
