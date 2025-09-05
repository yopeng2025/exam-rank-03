# 42 Exam Rank 03

This repository contains solutions for 42 School's Exam Rank 03, organized by difficulty levels.

## Structure

```
├── LEVEL-1/
│   ├── broken_gnl/     # Get Next Line implementation with fixes
│   ├── filter/         # String filtering and replacement program
│   └── scanf/          # Custom scanf implementation
└── LEVEL-2/
    ├── n_queens/       # N-Queens problem solver
    ├── permutations/   # String permutation generator
    ├── powerset/       # Subset sum problem solver
    ├── rip/           # Parentheses balancing problem
    └── tsp/           # Traveling Salesman Problem solver
```

## Level 1 Exercises

### broken_gnl
Implementation of `get_next_line` function that reads a file line by line.
- **Files**: `brocken_gnl.c`, `my_broken_gnl.c`
- **Key concepts**: File I/O, static variables, buffer management

### filter
Program that reads from stdin and replaces occurrences of a given word with asterisks.
- **Files**: `filter.c`, `filter2.c`
- **Usage**: `echo "hello world" | ./filter hello` → `***** world`
- **Key concepts**: String manipulation, memory management, stdin processing

### scanf
Custom implementation of `scanf` function supporting `%c`, `%d`, and `%s` format specifiers.
- **Files**: `scanf2.c`, `s.c`
- **Key concepts**: Variadic functions, format parsing, input validation

## Level 2 Exercises

### n_queens
Solves the N-Queens problem using backtracking algorithm.
- **Files**: `n_queens.c`, `my_n_queen.c`
- **Usage**: `./n_queens 4` outputs all valid queen placements on a 4x4 board
- **Key concepts**: Backtracking, recursion, constraint satisfaction

### permutations
Generates all permutations of a given string in alphabetical order.
- **Files**: `permutations.c`, `permutations2.c`
- **Usage**: `./permutations abc` → outputs all permutations of "abc"
- **Key concepts**: Recursion, backtracking, sorting algorithms

### powerset
Finds all subsets of a given set that sum to a target value.
- **Files**: `powerset.c`
- **Usage**: `./powerset 5 2 3` → outputs subsets that sum to 5
- **Key concepts**: Subset generation, dynamic programming concepts

### rip
Balances parentheses by removing the minimum number of characters.
- **Files**: `rip2.c`
- **Usage**: `./rip "(()"` → outputs all valid balanced strings
- **Key concepts**: String validation, backtracking, recursion

### tsp
Solves the Traveling Salesman Problem using brute force with optimizations.
- **Files**: `tsp.c`, `tsp_give.c`
- **Input format**: City coordinates as `x, y` pairs
- **Key concepts**: Graph algorithms, optimization, geometric calculations

## Compilation

Most programs can be compiled with:
```bash
gcc -Wall -Wextra -Werror *.c -o program_name
```

For TSP, add math library:
```bash
gcc -Wall -Wextra -Werror tsp.c -lm -o tsp
```

## Testing

Each exercise directory contains test files and expected outputs. The TSP directory includes multiple test cases with expected results.

## Key Learning Objectives

- **Algorithm Design**: Backtracking, recursion, optimization
- **Memory Management**: Dynamic allocation, proper cleanup
- **String Processing**: Parsing, manipulation, validation
- **File I/O**: Reading from files and stdin
- **Mathematical Concepts**: Combinatorics, graph theory, geometric calculations

## Notes

- All solutions follow 42 School's coding standards (Norminette)
- Error handling and edge cases are properly managed
- Memory leaks are avoided through proper cleanup
- Solutions are optimized for readability and efficiency

---

*This repository represents exam-level programming challenges that test fundamental computer science concepts and C programming skills.*
