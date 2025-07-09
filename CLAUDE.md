# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

```bash
# Build the program (optimized)
gcc -Ofast tangocount.c -o tangocount

# Build with debug symbols
gcc -g tangocount.c -o tangocount

# Run the program
./tangocount
```

## Code Architecture

This is a single-file C program that calculates the number of valid LinkedIn Tango puzzle grids of different sizes (2x2, 4x4, 6x6, 8x8, 10x10).

### Core Algorithm Components

- **Row Generation** (`generate_rows`): Pre-generates all valid row patterns for a given grid size. Valid rows have exactly n bits set and no three consecutive identical bits.

- **Column Validation** (`check_columns`): Validates that column constraints are satisfied during backtracking. Checks that no column has more than n bits set and implements early pruning optimizations.

- **Backtracking Solver** (`solve`): Uses depth-first search with pruning to find all valid grid configurations.

### Key Data Structures

- `rows[]`: Array storing all valid row bit patterns
- `grid[]`: Current grid state during solving (each element is a row represented as a bitmask)
- `grid_count`: Running count of valid solutions found

### Performance Characteristics

The algorithm uses bitwise operations extensively for efficiency. The `MAX_N` constant (currently 5) limits the maximum grid size to 10x10 due to memory and time constraints.

### Tango Puzzle Rules

- Grid size is always even (2n x 2n)
- Each row and column must have exactly n filled cells
- No three consecutive cells in any row or column can have the same value