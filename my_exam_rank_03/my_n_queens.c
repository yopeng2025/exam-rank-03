#include <stdio.h>
#include <stdlib.h>

void    print(int *board, int n)
{
    for(int i = 0, i < n, i++)
    {
        fprintf(stdout, "%d", board[i]);
        if (i < n - 1)
            fprintf(stdout, " ");
        else
            fprintf(stdout, "\n");              //双引号
    }
}

int check (int *board, int col, int row)
{
    for (int i = 0; i < col; i++)                       //用分号
    {
        if (board[i] == row || board[i] - row == col - i || row - board[i] == col - i)
            return 1;
    }
    return 0;
}

void    slove(int *board, int col, int n)
{
    if (col == n)
    {
        print(board, n);
        return ;
    }
    for(int row = 0; row < n; row++)                    //用分号
    {
        if(check(board, col, row) == 1)
        {
            board[col] = row;
            solve(board, col + 1, n);
        }
    }
}

int main(int ac, char **av)
{
    (void)ac;
    int n = atoi(av[1]);
    int *board = malloc(sizeof(int) * n);
    
    slove(board, 0, n);
    free(board);
}
