#ifndef RUSH01_H
#define RUSH01_H

#include <unistd.h>
#define N 4

// Function prototypes for main code 
void ft_putchar(char c);
void ft_putnmbr(int i);
void print_sqr(int sqr[N][N]);
void print_error(void);
int is_safe(int sqr[N][N], int row, int col, int num);
int check_rl(int sqr[N][N], int row, int inp);
int check_rr(int sqr[N][N], int row, int inp);
int check_cu(int sqr[N][N], int col, int inp);
int check_cd(int sqr[N][N], int col, int inp);
int check_sqr(int sqr[N][N], int inp[4 * N]);
int solve(int sqr[N][N], int row, int col, int inp[4 * N]);
int validate_input(char *str, int clues[4 * N]);

// Debugging function prototype 
int check_sqr_debug(int sqr[N][N], int inp[4 * N]);
void debug_print_grid(int sqr[N][N]);
#endif
