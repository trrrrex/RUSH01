/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:47:08 by annavram          #+#    #+#             */
/*   Updated: 2025/08/24 15:08:17 by annavram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}
//write on standard output
void    ft_putnmbr(int i)
{
    if (i >= 10)
        ft_putnmbr(i / 10);
    //convert to ASCII
    ft_putchar(i % 10 + '0');
}
//printing square matrix
void    print_sqr(int sqr[N][N])
{
    int i;
    int j;

    i = 0;
    while (i < N)
    {
        j = 0;
        while (j < N)
        {
            ft_putnmbr(sqr[i][j]);
            if (j < N - 1)
                ft_putchar(' ');
            j++;
        }
        ft_putchar('$');
        ft_putchar('\n');
        i++;
    }
}
//literally says error if there is an error
void    print_error(void)
{
    write(1, "Error\n", 6);
}
//validating if we can put the number
int     is_safe(int sqr[N][N], int row, int col, int num)
{
    int i;
    int j;

    j = 0;
    while (j < N)
    {
        if (sqr[row][j] == num)
        {
#ifdef DEBUG
            write(1, "Duplicate ", 10);
            ft_putnmbr(num);
            write(1, " in row ", 8);
            ft_putnmbr(row);
            ft_putchar('\n');
#endif
            return (0);
        }
        j++;
    }
    i = 0;
    while (i < N)
    {
        if (sqr[i][col] == num)
        {
#ifdef DEBUG
            write(1, "Duplicate ", 10);
            ft_putnmbr(num);
            write(1, " in col ", 8);
            ft_putnmbr(col);
            ft_putchar('\n');
#endif
            return (0);
        }
        i++;
    }
    return (1);
}
//check if we can see left row
int     check_rl(int sqr[N][N], int row, int inp)
{
    int max_h;
    int vision;
    int j;

    max_h = 0;
    vision = 0;
    j = 0;
    while (j < N)
    {
        if (sqr[row][j] > max_h)
        {
            max_h = sqr[row][j];
            vision++;
        }
        j++;
    }
    return (vision == inp);
}
//check if we can see right row
int     check_rr(int sqr[N][N], int row, int inp)
{
    int max_h;
    int vision; //keeps track on how many boxes we see
    int j;

    max_h = 0;
    vision = 0;
    j = N - 1;
    while (j >= 0)
    {
        if (sqr[row][j] > max_h)
        {
            max_h = sqr[row][j];
            vision++;
        }
        j--;
    }
    return (vision == inp);
}
// it checks the column from up to buttom
int     check_cu(int sqr[N][N], int col, int inp)
{
    int max_h;
    int vision;
    int i;

    max_h = 0;
    vision = 0;
    i = 0;
    while (i < N)
    {
        if (sqr[i][col] > max_h)
        {
            max_h = sqr[i][col];
            vision++;
        }
        i++;
    }
    return (vision == inp);
}
// the same but from buttom to up
int     check_cd(int sqr[N][N], int col, int inp)
{
    int max_h;
    int vision;
    int i;

    max_h = 0;
    vision = 0;
    i = N - 1;
    while (i >= 0)
    {
        if (sqr[i][col] > max_h)
        {
            max_h = sqr[i][col];
            vision++;
        }
        i--;
    }
    return (vision == inp);
}
// checks the sqr
int     check_sqr(int sqr[N][N], int inp[4 * N])
{
    int i;

    i = 0;
    while (i < N)
    {
        if (!check_cu(sqr, i, inp[i]) ||
            !check_cd(sqr, i, inp[i + N]) ||
            !check_rl(sqr, i, inp[i + 2 * N]) ||
            !check_rr(sqr, i, inp[i + 3 * N]))
            return (0);
        i++;
    }
    return (1);
}
//algoritmo
int     solve(int sqr[N][N], int row, int col, int inp[4 * N])
{
    int i;

    if (row == N)
    {
#ifdef DEBUG
        write(1, "Checking full grid:\n", 19);
        debug_print_grid(sqr);
        return (check_sqr_debug(sqr, inp));
#else
        return (check_sqr(sqr, inp));
#endif
    }
    if (col == N)
    {
#ifdef DEBUG
        write(1, "Moving to next row: ", 20);
        ft_putnmbr(row + 1);
        ft_putchar('\n');
#endif
        return (solve(sqr, row + 1, 0, inp));
    }
    i = 1;
    while (i <= N)
    {
        if (is_safe(sqr, row, col, i))
        {
#ifdef DEBUG
            write(1, "Trying ", 7);
            ft_putnmbr(i);
            write(1, " at (", 5);
            ft_putnmbr(row);
            ft_putchar(',');
            ft_putnmbr(col);
            write(1, ")\n", 2);
            debug_print_grid(sqr);
#endif
            sqr[row][col] = i;
            if (solve(sqr, row, col + 1, inp))
                return (1);
            sqr[row][col] = 0;
#ifdef DEBUG
            write(1, "Backtracking from (", 19);
            ft_putnmbr(row);
            ft_putchar(',');
            ft_putnmbr(col);
            write(1, ")\n", 2);
#endif
        }
        i++;
    }
#ifdef DEBUG
    write(1, "No valid number at (", 19);
    ft_putnmbr(row);
    ft_putchar(',');
    ft_putnmbr(col);
    write(1, ")\n", 2);
#endif
    return (0);
}

int     check_input_char(char c, char next)
{
    if (c >= '1' && c <= '4' && (next == ' ' || next == '\0'))
        return (1);
    return (0);
}
// this is bugged
/*
int     validate_input(char *str, int clues[4 * N])
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (count >= 4 * N)
        {
#ifdef DEBUG
            write(1, "Too many clues\n", 15);
#endif
            return (0);
        }
        if (check_input_char(str[i], str[i + 1]))
        {
            clues[count] = str[i] - '0';
            count++;
            i += 2;
            if (str[i] == '\0' && count == 4 * N)
                break;
        }
        else
        {
#ifdef DEBUG
            write(1, "Invalid input at position ", 25);
            ft_putnmbr(i);
            write(1, ": char '", 8);
            ft_putchar(str[i]);
            write(1, "'\n", 2);
#endif
            return (0);
        }
    }
    if (count != 4 * N)
    {
#ifdef DEBUG
        write(1, "Too few clues: ", 15);
        ft_putnmbr(count);
        ft_putchar('\n');
#endif
        return (0);
    }
#ifdef DEBUG
    write(1, "Clues: ", 7);
    i = 0;
    while (i < 4 * N)
    {
        ft_putnmbr(clues[i]);
        ft_putchar(' ');
        i++;
    }
    ft_putchar('\n');
#endif
    return (1);
}*/
int     validate_input(char *str, int clues[4 * N])
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (count < 4 * N && str[i])
    {
        if (!check_input_char(str[i], str[i + 1]))
        {
#ifdef DEBUG
            write(1, "Invalid input at position ", 25);
            ft_putnmbr(i);
            write(1, ": char '", 8);
            ft_putchar(str[i]);
            write(1, "'\n", 2);
#endif
            return (0);
        }
        clues[count] = str[i] - '0';
        count++;
        i += 2;
    }
    if (count != 4 * N)
    {
#ifdef DEBUG
        write(1, "Too few clues: ", 15);
        ft_putnmbr(count);
        ft_putchar('\n');
#endif
        return (0);
    }
#ifdef DEBUG
    write(1, "Clues: ", 7);
    i = 0;
    while (i < 4 * N)
    {
        ft_putnmbr(clues[i]);
        ft_putchar(' ');
        i++;
    }
    ft_putchar('\n');
#endif
    return (1);
}

//hardcoded main (works!)
/*
int     main(int argc, char *argv[])
{
    char *test_input;
    int clues[4 * N];
    int sqr[N][N] = {{0}};

    test_input = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2";
#ifdef DEBUG
    {
        int i;

        write(1, "Input: ", 7);
        i = 0;
        while (test_input[i])
        {
            ft_putchar(test_input[i]);
            i++;
        }
        ft_putchar('\n');
    }
#endif
    if (!validate_input(test_input, clues))
    {
        print_error();
        return (1);
    }
    if (solve(sqr, 0, 0, clues))
        print_sqr(sqr);
    else
        print_error();
    return (0);
}*/

int     main(int argc, char *argv[])
{
    int clues[4 * N];
    int sqr[N][N] = {{0}};

    if (argc != 2)
    {
        print_error();
        return (1);
    }
#ifdef DEBUG
    {
        int i;

        write(1, "Input: ", 7);
        i = 0;
        while (argv[1][i])
        {
            ft_putchar(argv[1][i]);
            i++;
        }
        ft_putchar('\n');
    }
#endif
    if (!validate_input(argv[1], clues))
    {
        print_error();
        return (1);
    }
    if (solve(sqr, 0, 0, clues))
        print_sqr(sqr);
    else
        print_error();
    return (0);
}
