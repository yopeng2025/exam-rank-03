#include <unistd.h>		//read write
#include <stdlib.h>		//malloc free
#include <string.h>   	//strlen

int	ft_strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	while(i < n && s1[i] == s2[i])
		i++;
	if(i == n)
		return 1;
	else
		return 0;
}


int main(int ac, char **av)
{
	char	*buff = malloc(1000000);
	char	*tmp = av[1];
	char	c;
	int		r = read(0, &c, 1);
	int		i = 0;
	int		j = 0;
	int		len = strlen(av[1]);
	(void)ac;

	while(r > 0)
	{
		buff[i++] = c;
		r = read(0, &c, 1);
	}
	buff[i] = '\0';
	i = 0;
	while(buff[i] != '\0')
	{
		if(ft_strncmp(&buff[i], tmp, len) == 1)
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
			write(1, &buff[i], 1);
			i++;
		}
	}
	free(buff);
}
