#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (char *)s;
		s++;
	}
	return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;								// MODIF
	while (i < n)								// MODIF
	{											// MODIF
		((char *)dest)[i] = ((char *)src)[i];	// MODIF
		i++;									// MODIF
	}											// MODIF
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
	// Si s1 n'est pas defini on passe en force
	size_t size1;								// MODIF
	if (*s1)									// MODIF
		size1 = ft_strlen(*s1);					// MODIF
	else										// MODIF
		size1 = 0;								// MODIF
	char *tmp = malloc(size2 + size1 + 1);
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
	return str_append_mem(s1, s2, ft_strlen(s2));
}

// PAS BESOIN DE ft_memmove on utilise ft_memcpy

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
			if (ret)							// +
				free (ret);						// +
			return NULL;
		}
		b[read_ret] = 0;
		// Plus rien a lire
		if (read_ret == 0)						// +
		{										// +
			if (ret && *ret)					// +
				return ret;						// +
			free(ret);							// +
			return NULL;						// +
		}										// +
		tmp = ft_strchr(b, '\n');				// +
	}
	if (!str_append_mem(&ret, b, tmp - b  + 1))
	{
		free(ret);
		return (NULL);
	}
	// decaler de 1 avec le reste 
	ft_memcpy(b, tmp + 1, ft_strlen(tmp + 1) + 1); // +
	return ret;
}

int main(int argc, char **argv)
{
	int fd;
	char *line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		return 1;
	}

	while ((line = get_next_line(fd)) != NULL) {
		printf("%s", line);
		free(line);
	}

	close(fd);
	return 0;
}

