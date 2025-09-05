// ft_scanf.c
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    int consumed = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (!isspace(c))
        {
            ungetc(c, f);
            break;
        }
        consumed = 1;
    }
    if (ferror(f))
        return -1;
    // 返回 1 表示匹配到至少一个空白，否则返回 0（与上层逻辑兼容）
    return consumed ? 1 : 0;
}

int match_char(FILE *f, char c)
{
    int ch = fgetc(f);
    if (ch == EOF)
        return -1; // 输入耗尽或错误
    if (ch == (unsigned char)c)
        return 1;  // 成功匹配
    // 不匹配则回推该字符供上层决定，但 scanf 语义是失败并停止
    ungetc(ch, f);
    return 0;
}

int scan_char(FILE *f, va_list ap)
{
    int ch = fgetc(f);
    if (ch == EOF)
        return 0; // 转换失败
    char *dst = va_arg(ap, char *);
    if (!dst)
        return 0;
    *dst = (char)ch;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int c;
    int neg = 0;
    long val = 0; // 用 long 聚合，最后存到 int（题目允许不处理溢出）

    // 跳过前导空白
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
    if (c == EOF)
        return 0;

    // 处理符号
    if (c == '+' || c == '-')
    {
        neg = (c == '-');
        int next = fgetc(f);
        if (next == EOF)
            return 0;
        if (!isdigit(next))
        {
            // 符号后不是数字 -> 失败，需要把 next 回推，符号也回推
            ungetc(next, f);
            ungetc(c, f);
            return 0;
        }
        c = next;
    }
    else if (!isdigit(c))
    {
        // 既不是空白也不是符号数字 -> 回推并失败
        ungetc(c, f);
        return 0;
    }

    // 至少有一个数字
    do
    {
        val = val * 10 + (c - '0');
        c = fgetc(f);
    } while (c != EOF && isdigit(c));

    if (c != EOF)
        ungetc(c, f);

    int *dst = va_arg(ap, int *);
    if (!dst)
        return 0;

    if (neg) val = -val;
    *dst = (int)val;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int c;
    char *dst = va_arg(ap, char *);
    if (!dst)
        return 0;

    // 跳过前导空白
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
    if (c == EOF)
        return 0;

    // 读取直到下一个空白或 EOF
    int n = 0;
    do
    {
        if (isspace(c))
        {
            ungetc(c, f);
            break;
        }
        dst[n++] = (char)c;
        c = fgetc(f);
    } while (c != EOF);

    // 至少要读到一个字符
    if (n == 0)
    {
        if (c != EOF)
            ungetc(c, f);
        return 0;
    }

    dst[n] = '\0';
    return 1;
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace((unsigned char)*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}

	if (ferror(f))
		return EOF;
	return nconv == 0 && feof(f) ? EOF : nconv;
}

int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
