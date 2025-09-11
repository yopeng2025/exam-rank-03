#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

size_t  ft_strlen(const char *s)
{
	size_t  i;

	i = 0;
	while(*s)
	{
		s++;
		i++;
	}
	return (i);
}

char    *ft_strchr(const char *s, int c)
{
	while(*s)
	{
		if(*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t  i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while(i < n)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dst);  //只复制字符，不负责结束符
}

void    *ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char       *d;
	const unsigned char *s;

	if (!dst && !src)
		return (NULL);
	if (dst == src || n == 0)
		return (dst);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d > s)
	{
		while(n--)
			d[n] = s[n];
	}
	else
	{
		while(n--)
			*d++ = *s++;
	}
	return (dst); //同样只复制字符，不负责结束符，但是考虑dst和src的位置
}

//成功返回1 失败返回0
int    str_append_mem(char **s1, const char *s2, size_t size2) //s1指针
{
	size_t  size1;
	char    *tmp;

	if (*s1)
		size1 = ft_strlen(*s1);          //传入str (char*) 而不是指针s1
	else
		size1 = 0;
	tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return (0);						      //失败return0
	if (size1 > 0)
		ft_memcpy(tmp, *s1, size1);           //*s1才是字符串，不是s1
	if (size2 > 0 && s2 != NULL)			  //s2不能是空的\0
		ft_memcpy(tmp+size1, s2, size2);      //tmp[size1]后面+tmp[size2]
	tmp[size1 + size2] = '\0';
	if (*s1 != NULL)							//*s1才是字符串！
		free (*s1);
	*s1 = tmp;
	return (1);									//成功返回1
}

int str_append_str(char **s1, const *s2)				//s1是指针
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

char    *get_next_line(int fd)
{
	static char    b[BUFFER_SIZE + 1];
	char    *nl;
	char    *ret = NULL;					//分配好
	size_t  take;
	ssize_t r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		nl = ft_strchr(b, '\n');
		if (nl != NULL)
		{
			take = (size_t)(nl - b) + 1;
			if(!str_append_mem(&ret, b, take))
			{
				free(ret);
				return (NULL);
			}
			ft_memmove(b, b + take, ft_strlen(b + take) + 1);
			return(ret);
		}
		if(b[0] != '\0')
		{
			if(!str_append_str(&ret, b))
			{
				free(ret);
				return (NULL);
			}
			b[0] = '\0';
		}
		
		r = read(fd, b, BUFFER_SIZE);			
		if (r < 0)
		{
			free(ret);						//ret被append时被malloc过，需要free
			b[0] = '\0';					//静态变量清零
			return (NULL);
		}
		if (r == 0)
		{
			if (ret != NULL && *ret != '\0')
			{
				b[0] = '\0';				//静态变量清零
				return (ret);
			}
			return (NULL);
		}
		b[r] = '\0';
	}
	
}

int main(int argc, char **argv)
{
	int     fd;
	char    *line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);  //0 stdin, 1 stdout, 2 stderr, -1,error
		if (fd < 0)
			return (1);
		while((line = get_next_line(fd)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
	}
	close(fd);
	return (0);
}