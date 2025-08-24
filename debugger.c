*/
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:48:13 by annavram          #+#    #+#             */
/*   Updated: 2025/08/24 14:48:18 by annavram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

void    debug_print_grid(int sqr[N][N])
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
            ft_putchar(' ');
            j++;
        }
        ft_putchar('\n');
        i++;
    }
}

int     check_col_up(int sqr[N][N], int col, int inp)
{
    int max_h;
    int vision;
    int j;

    max_h = 0;
    vision = 0;
    j = 0;
    while (j < N)
    {
        if (sqr[j][col] > max_h)
        {
            max_h = sqr[j][col];
            vision++;
        }
        j++;
    }
    if (vision != inp)
    {
        write(1, "col_up failed for col ", 21);
        ft_putnmbr(col);
        write(1, ": expected ", 10);
        ft_putnmbr(inp);
        write(1, ", got ", 6);
        ft_putnmbr(vision);
        write(1, "\nGrid:\n", 7);
        debug_print_grid(sqr);
        return (0);
    }
    return (1);
}

int     check_col_down(int sqr[N][N], int col, int inp)
{
    int max_h;
    int vision;
    int j;

    max_h = 0;
    vision = 0;
    j = N - 1;
    while (j >= 0)
    {
        if (sqr[j][col] > max_h)
        {
            max_h = sqr[j][col];
            vision++;
        }
        j--;
    }
    if (vision != inp)
    {
        write(1, "col_down failed for col ", 23);
        ft_putnmbr(col);
        write(1, ": expected ", 10);
        ft_putnmbr(inp);
        write(1, ", got ", 6);
        ft_putnmbr(vision);
        write(1, "\nGrid:\n", 7);
        debug_print_grid(sqr);
        return (0);
    }
    return (1);
}

int     check_row_left(int sqr[N][N], int row, int inp)
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
    if (vision != inp)
    {
        write(1, "row_left failed for row ", 23);
        ft_putnmbr(row);
        write(1, ": expected ", 10);
        ft_putnmbr(inp);
        write(1, ", got ", 6);
        ft_putnmbr(vision);
        write(1, "\nGrid:\n", 7);
        debug_print_grid(sqr);
        return (0);
    }
    return (1);
}

int     check_row_right(int sqr[N][N], int row, int inp)
{
    int max_h;
    int vision;
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
    if (vision != inp)
    {
        write(1, "row_right failed for row ", 24);
        ft_putnmbr(row);
        write(1, ": expected ", 10);
        ft_putnmbr(inp);
        write(1, ", got ", 6);
        ft_putnmbr(vision);
        write(1, "\nGrid:\n", 7);
        debug_print_grid(sqr);
        return (0);
    }
    return (1);
}

int     check_sqr_debug(int sqr[N][N], int inp[4 * N])
{
    int i;

    i = 0;
    while (i < N)
    {
        if (!check_col_up(sqr, i, inp[i]))
            return (0);
        if (!check_col_down(sqr, i, inp[i + N]))
            return (0);
        if (!check_row_left(sqr, i, inp[i + 2 * N]))
            return (0);
        if (!check_row_right(sqr, i, inp[i + 3 * N]))
            return (0);
        i++;
    }
    return (1);
}
