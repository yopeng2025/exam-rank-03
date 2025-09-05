#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while(*s)
	{
		if (*s == (char)c)						//参数用 int：历史原因 + 接口统一 + 表达范围更稳。转换为char以比较字符
			return ((char *)s);					//返回指针，指向字符,返回此字符直至\0
		*s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if(!dest && !src)
		return (NULL);
	i = 0;
	while(i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i]; //unsigned把内存当“原始字节(0..255)”来处理
		i++;														  //在比较/运算/打印等场景比char更可靠
	}
	return (dest);
}
