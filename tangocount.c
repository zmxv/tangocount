#include <stdio.h>
#include <time.h>

#define MAX_N 5
#define MAX_GRID_SIZE (MAX_N + MAX_N)
#define MAX_ROWS 1024

static int rows[MAX_ROWS];
static int row_count = 0;
static int grid[MAX_GRID_SIZE];
static long grid_count = 0;

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
    for (int col = 0; col < n + n; col++) {
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
    for (int i = 0; i < row_count; i++) {
        grid[level] = rows[i];
        if (check_columns(n, level + 1)) {
            if (level + 1 == n + n) {
                grid_count++;
            } else {
                solve(level + 1, n);
            }
        }
    }
}

void generate_rows(int n) {
    row_count = 0;
    int max_val = (1 << (n * 2)) - 1;
    
    for (int i = max_val; i >= 0; i--) {
        // Count set bits
        int sum = 0;
        for (int j = 0; j < n * 2; j++) {
            if ((i >> j) & 1) {
                sum++;
            }
        }
        
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
        solve(0, n);
        double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
        printf("%dx%d => %ld grids\t%.3fs\n", n*2, n*2, grid_count, duration);
    }
    return 0;
}