#include "get_next_line.h"								
//#include <stdlib.h>
//#include <unistd.h>
//#include <stdio.h>
//#include <fcntl.h>

//#ifndef BUFFER_SIZE
//# define BUFFER_SIZE 100
//#endif

size_t ft_strlen(char *s)
{
	size_t i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

char  *ft_strchr(const char *s, int c)                  //参数 s 应该是 const char *
{
	int i = 0;
	while (s[i] != c)									//c 需要转为 (char) 再比较
		i++;
	if (s[i]  == c)
		return (s+i);
	else
		return (NULL);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	while (--n > 0)
		((char *)dest)[n - 1] = ((char *)src)[n - 1];
	return dest;
}

/*标准 memcpy：逐字节从头到尾拷贝；当 n==0 时不进入循环；允许 dest/src 皆为 NULL 时直接返回 NULL */
/*void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t	i;

    if (!dst && !src)
        return NULL;
    i = 0;
    while (i < n)
    {
        ((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
        i++;
    }
    return dst;
}*/

void  *ft_memmove (void *dest, const void *src, size_t n)
{
	if (dest > src)
		return ft_memcpy(dest, src, n);
	else if (dest == src)
		return dest;
		size_t i = ftstrlen((char*)src + 1);
	while (i >= 0)
	{
		((char *) dest)[i] = ((char *) src)[i];
		i--;
	}
	return (dest);
}
/*
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	if (dest == src || n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

*/
int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
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
/*
int str_append_mem(char **s1, const char *s2, size_t size2)
{
    size_t size1;
    char   *tmp;

    if (*s1 == NULL)
        size1 = 0;
    else
        size1 = ft_strlen(*s1);

    tmp = (char *)malloc(size1 + size2 + 1);
    if (!tmp)
        return 0;

    if (size1 > 0)
        ft_memcpy(tmp, *s1, size1);
    if (size2 > 0 && s2 != NULL)
        ft_memcpy(tmp + size1, s2, size2);

    tmp[size1 + size2] = '\0';

    if (*s1 != NULL)
        free(*s1);
    *s1 = tmp;
    return 1;
}

int str_append_str(char **s1, const char *s2)
{
    return str_append_mem(s1, s2, ft_strlen(s2));
}
*/
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
			return NULL;
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b  + 1))
	{
		free(ret);
		return (NULL);
	}
	return ret;
}
/*
char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char        *ret = NULL;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1)
    {
        char *nl = ft_strchr(b, '\n');
        if (nl != NULL)
        {
            size_t take = (size_t)(nl - b) + 1;              /* 包含 '\n' */
            if (!str_append_mem(&ret, b, take))             
            {
                free(ret);
                return NULL;
            }
            ft_memmove(b, b + take, ft_strlen(b + take) + 1);  /* 把剩余内容前移，留到下次 */
            return ret;
        }

        /* 缓冲区中没有 '\n'，先把整个 b 追加到 ret，然后读新数据 */
        if (*b != '\0')
        {
            if (!str_append_str(&ret, b))
            {
                free(ret);
                return NULL;
            }
            b[0] = '\0';
        }

        /* 读取新数据 */
        ssize_t r = read(fd, b, BUFFER_SIZE);
        if (r < 0)
        {
            free(ret);
            b[0] = '\0';
            return NULL;
        }
        if (r == 0)
        {
            /* EOF：若已有累积则返回它（可能不含 '\n'），否则返回 NULL */
            if (ret != NULL && *ret != '\0')
            {
                b[0] = '\0';
                return ret;
            }
            return NULL;
        }
        b[r] = '\0';
        /* 回到循环顶部，重新查找 '\n' */
    }
}
*/