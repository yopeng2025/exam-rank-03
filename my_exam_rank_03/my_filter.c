#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int ft_strncmp(char *s1, char *s2, int n)
{
	int  i = 0;

	while (i < n && s1[i] == s2[i])
		i++;
	if (i == n)
		return 1;
	else
		return 0;
}

int main (int ac, char **av)
{
	char    *buf = malloc(1000000);
	char    *tmp = av[1];
	char    c;
	int     i = 0;
	int     j = 0;
	int		len = strlen(av[1]);
	int     r = read(0, &c, 1);
	(void)ac;

	while (r > 0)
	{
		buf[i] = c;
		r = read(0, &c, 1);
		i++;
	}
	buf[i] = '\0';

	i = 0;
	while (buf[i] != '\0')
	{
		if(ft_strncmp(&buf[i], tmp, len) == 1)
		{
			j = 0;
			while (j < len)
			{
				write(1, "*", 1);
				j++;
			}
			i = i + len;
		}
		else
		{
			write(1, &buf[i], 1);
			i++;
		}
	}
	free(buf);
}