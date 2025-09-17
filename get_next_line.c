#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef  BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char  *ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i = 0;

	while (i < n)
	{
		((char *)dest)[i] = ((const char *)src)[i];
		i++;
	}
	return dest;
}

size_t ft_strlen(char *s)
{
	size_t ret = 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1;

	if(*s1)
		size1 = ft_strlen(*s1);
	else
		size1 = 0;

	char *tmp = malloc(size2 + size1 +1);
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return 1;
}

int str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
		{
			if (ret)
				free(ret);
			return NULL;
		}

		b[read_ret] = 0;

		if (read_ret == 0)
		{
			if(ret && *ret)
				return ret;
			free(ret);
			return NULL;
		}
		
		tmp = ft_strchr(b, '\n');
	}


	if (!str_append_mem(&ret, b, tmp - b  + 1))
	{
		free(ret);
		return (NULL);
	}

	ft_memcpy(b, tmp+1, ft_strlen(tmp+1)+1);
	return ret;
}

int	main(int ac, char **av)
{
	int		fd;
	char *line;

	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	if(fd < 0)
		return 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
