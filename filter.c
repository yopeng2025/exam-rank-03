#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ft_strncmp(char *s1, char *s2, int n)
{
    int i = 0;

    while (i < n && s1[i] == s2[i])
        i++;
    if (i == n)
        return 1;
    else
        return 0;
}

int main(int ac, char **av)
{
    char    *b = malloc(1000000);
    char    *tmp = av[1];
    char    c;
    int     r = read(0, &c, 1);
    int     i = 0;
    int     j = 0;
    int     len = strlen(av[1]);

    while (r > 0)
    {
        b[i] = c;
        r = read(0, &c, 1);
        i++;
    }
    b[i] = '\0';

    i = 0;
    while (b[i])
    {
        if (ft_strncmp(&b[i], tmp, len) == 1)
        {
            j = 0;
            while (j < len)
            {
                write(1, "*", 1);
                j++;
            }
            i += len;
        }
        else
        {
            write(1, &b[i], 1);
            i++;
        }
    }
    free(b);
}