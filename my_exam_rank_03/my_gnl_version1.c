#include <unistd.h> //read, write, close
#include <stdio.h>  //printf, perror, fprintf
#include <stdlib.h> //malloc / free / calloc / realloc
#include <fcntl.h>  //open, O_RDONLY

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)        //返回指针，指向字符
{
	while(*s)
	{
		if (*s == (char)c)						//参数用 int：历史原因 + 接口统一 + 表达范围更稳。转换为char以比较字符
			return ((char *)s);					//返回指针，指向字符,返回此字符直至\0
		s++;									//修正*s++ ---> 为s++
	}
	if ((char)c == '\0')						//*s已经到底了\0
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if(!dst && !src)
		return (NULL);
	i = 0;
	while(i < n)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];  //unsigned把内存当“原始字节(0..255)”来处理
		i++;														  //在比较/运算/打印等场景比char更可靠
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char 		*d;
	const unsigned char	*s;

	if(!dst && !src)
		return (NULL);
	if (dst == src || n == 0)
        return (dst);
	d = (unsigned char *)dst;		//比较 dest > src 前也应把它们转为同一类型的字节指针再比
	s = (const unsigned char *)src;
	if(d > s)					// 可能重叠且目标在后：从尾到头拷贝，避免覆盖未拷贝的数据
	{
		while(n--)
			d[n] = s[n];
	}
	else						// 不重叠或目标在前：从头到尾拷贝
	{
		while(n--)
			*d++ = *s++;        //char赋值(char)*d，然后指针移动去下一个d++
	}
	return (dst);
}

/*给*s1重新分配一块更大的内存，把旧内容拷过去，再把 s2 的内容接在后面*/
int	str_append_mem(char **s1, const char *s2, size_t size2)   //成功返回1 失败返回0； char**字符串指针，用于修改字符串
{
	char 	*tmp;										
	size_t	size1;										//size2 -> s2的长度（要追加的字节数）

	if(*s1 != NULL)
		size1 = ft_strlen(*s1);
	else
		size1 = 0;
	tmp = malloc(size1 + size2 + 1);
	if(!tmp)
		return (0);
	if(size1 > 0)
		ft_memcpy(tmp, *s1, size1);			//如s1有内容，复制到tmp中
	if(size2 > 0 && s2 != NULL)
		ft_memcpy(tmp+size1, s2, size2);    //如s2不为空且长度大于0,把s2内容复制到tmp（size1长度）后面
											//即s1+s2
	tmp[size1 + size2] = '\0';
	if(*s1 != NULL)							//释放s1内容
		free(*s1);
	*s1 = tmp;								//将tmp(s1+s2)内容放入s1
	return (1);
}

int	str_append_str(char **s1, const char *s2)
{
	return(str_append_mem(s1, s2, ft_strlen(s2)));
}


char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];		//静态自动初始化为0 char buf={'\0', '\0', ... ,'\0'}
	char		*rt = NULL;					//return，即每一行显示的内容
	char		*nl;						//newline
	size_t		take;
	ssize_t		r;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while(1)
	{
		nl = ft_strchr(buf, '\n');			//找出buffer中的\n，nl指针指向buf中的\n
		if (nl != NULL)
		{
			take = (size_t)(nl - buf) + 1;    //即‘\n’+‘\n’前面的字符串数量；buf → 缓冲区的起始地址（指向 b[0]） nl → 指向buf里面找到的第一个 '\n'
			if (!str_append_mem(&rt, buf, take))//将buffer的前take个字符添加到rt
			{
				free(rt);
				return (NULL);
			}
			ft_memmove(buf, buf + take, ft_strlen(buf + take) + 1); //take后面的内容(剩余串+结尾'\0')往前移动变成新的字符串
			return (rt);
		}
		if (buf[0] != '\0')					//没有找到\n，且buf还有内容
		{
			if(!str_append_str(&rt, buf))   //将buf的内容复制到rt
			{
				free(rt);
				return (NULL);
			}
			buf[0] = '\0';					//清空buf
		}

		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
		{
			free(rt);
			buf[0] = '\0';
			return (NULL);
		}
		if (r == 0)				//read()的返回值 >0实际读取字节数 =0 EOF -1出错
		{
			if (rt != NULL && *rt != '\0') //rt被分配过内容，且rt第一个字符有内容
			{
				buf[0] = '\0';
				return (rt);
			}
			return (NULL);
		}
		buf[r] = '\0';			//回到循环顶部，重新查找'\n'
	}
}

int main(int argc, char **argv)
{
	int fd;
	char *line;
	
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);           //0 → 标准输入 (stdin) 1 → 标准输出 (stdout) 2 → 标准错误 (stderr) -1 error
	if (fd < 0)
		return 1;

	while ((line = get_next_line(fd)) != NULL) {
		printf("%s", line);
		free(line);
	}

	close(fd);
	return 0;
}