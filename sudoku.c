#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void display(int* grid) {
    for (int r=0; r<9; r++) {
        if (r%3 == 0) {printf("+-------+-------+-------+\n");}
        for (int c=0; c<9; c++) {
            if (c%3 == 0) {printf("| ");}
            if (grid[r*9+c] == 0) {printf("  ");}
            else {printf("%d ", grid[r*9+c]);}
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
}

bool valid(int* grid, int r, int c, int sub, int v) {
    for (int i=0; i<9; i++) {
        if (grid[i*9+c] == v || grid[r*9+i] == v || grid[(i%3)*9+i/3+sub] == v) {
            return false;
        }
    }
    return true;
}

bool solve(int* grid, int i) {
    if (i == 81) {return true;}
    if (grid[i] != 0) {return solve(grid, i+1);}
    int r = i/9;
    int c = i%9;
    int sub = (r/3)*27+(c/3)*3;
    for (int v=1; v<=9; v++) {
        if (valid(grid, r, c, sub, v)) {
            grid[i] = v;
            if (solve(grid, i+1)) {return true;}
        }
    }
    grid[i] = 0;
    return false;
}

int main(int argc, char* argv[]) {
    int grid[] = {0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0};
    solve(grid, 0);
    display(grid);
    printf("end");
    return 0;
}