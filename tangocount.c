#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_N 5
#define MAX_GRID_SIZE (MAX_N + MAX_N)
#define MAX_ROWS 1024

static int rows[MAX_ROWS];
static int row_count = 0;
static int grid[MAX_GRID_SIZE];
static long grid_count = 0;

// Expected results for sanity checking
static const long expected_results[] = {
    2L,          // 2x2
    90L,         // 4x4
    11222L,      // 6x6
    12413918L,   // 8x8
    117925227108L // 10x10
};

void verify_result(int n, long result) {
    if (n <= 5 && result != expected_results[n-1]) {
        printf("ERROR: Expected %ld for %dx%d, got %ld\n", 
               expected_results[n-1], n*2, n*2, result);
        exit(1);
    }
}

int check_columns(int n, int level) {
    // Early return for lower levels
    if (n > 1 && level < 3) {
        return 1;
    }

    // Check consecutive patterns
    if (level >= 3 && ((grid[level-3] | grid[level-2] | grid[level-1]) ^ 
                     (grid[level-3] & grid[level-2] & grid[level-1])) != (1 << (n + n)) - 1) {
        return 0;
    }

    // Check column sums
    for (int col = n + n - 1; col >= 0; col--) {
        int sum = 0;
        for (int row = 0; row < level; row++) {
            sum += (grid[row] >> col) & 1;
        }
        if (sum > n || (level - sum) > n) {
            return 0;
        }
    }
    return 1;
}

void solve(int level, int n) {
    if (level + 1 == n + n) {
        for (int i = row_count - 1; i >= 0; i--) {
            grid[level] = rows[i];
            if (check_columns(n, level + 1)) {
                grid_count++;
            }
        }
    } else {
        for (int i = row_count - 1; i >= 0; i--) {
            grid[level] = rows[i];
            if (check_columns(n, level + 1)) {
                solve(level + 1, n);
            }
        }
    }
}

void solve_0(int n) {
    for (int i = row_count / 2 - 1; i >= 0; i--) {
        grid[0] = rows[i];
        solve(1, n);
    }
}

void generate_rows(int n) {
    row_count = 0;
    int max_val = (1 << (n * 2)) - 1;
    
    for (int i = max_val; i >= 0; i--) {
        // Count set bits using builtin function
        int sum = __builtin_popcount(i);
        
        if (sum == n) {
            // Check for three consecutive bits
            int valid = 1;
            for (int j = 2; j < n * 2; j++) {
                int a = (i >> (j - 2)) & 1;
                int b = (i >> (j - 1)) & 1;
                int c = (i >> j) & 1;
                if (a == b && b == c) {
                    valid = 0;
                    break;
                }
            }
            
            if (valid) {
                rows[row_count++] = i;
            }
        }
    }
}

int main() {
    for (int n = 1; n <= MAX_N; n++) {
        clock_t start = clock();
        generate_rows(n);
        grid_count = 0;
        solve_0(n);
        
        // Apply symmetry optimization: multiply by 2 since we only tried half the rows at level 0
        grid_count *= 2;
        
        double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
        
        // Verify result against expected values
        verify_result(n, grid_count);
        
        printf("%dx%d => %ld grids\t%.3fs\n", n*2, n*2, grid_count, duration);
    }
    printf("All sanity checks passed!\n");
    return 0;
}