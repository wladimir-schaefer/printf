/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:48:17 by wschafer          #+#    #+#             */
/*   Updated: 2025/05/29 11:48:22 by wschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

static	int	putstr(char *s);
static	int	putchar(int i);
static	int	print_pointer(void *p);
static	int itoa(int i);
static	int	utoa(unsigned u);
static	int	print_hex(unsigned u, int uppercase);


int	ft_printf(const char *s, ...)
{
	va_list		args;
	int			count;

	count = 0;
	va_start(args, s);	
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s == 'c')
				count += putchar(va_arg(args, int));
			if (*s == 's')
				count += putstr(va_arg(args, char*));
			if (*s == 'p')
				count += print_pointer(va_arg(args, void *));
			if (*s == 'd' || *s == 'i')
				count += itoa(va_arg(args, int));
			if (*s == 'u')
				count += utoa(va_arg(args, unsigned));
			if (*s == 'x')
				count += print_hex(va_arg(args, unsigned), 0);
			if (*s == 'X')
				count += print_hex(va_arg(args, unsigned), 1);
			if (*s == '%')
				count += putchar('%');
		}
		else
		{
			count += write(1, s, 1);			
		}
		s++;
	}
	va_end(args);
	return(count);
}

#include <stdio.h>
int	main()
{
//	char c = 'C';
//	char *str = "abcdef";
//	int i = -123;
	unsigned u = 305441741; //prints: 1234abcd

	printf("%d\n",ft_printf("www %X mmm %%%%\n", u));
//	ft_printf("www %p mmm\n", i);
//	printf("%x\n", 123);
}

static	int	putchar(int i)
{
	char	c;

	c = (char)i;
	if (write(1, &c, 1) != 1)
		return (-1);
	return (1);
}

static	int	putstr(char *s)
{
	int	len;

	len = 0;
	if (!s)
		s = "(null)";
	while (*s)
	{
		if(write(1, s, 1) != 1)
			return (-1);
		s++;
		len++;
	}
	return (len);
}

static	int	print_pointer(void *p)
{
	int		len;
	int		i;
	char	*base = "0123456789abcdef";
	char	buffer[16];
	unsigned long	ptr;

	if (!p)
		return(write(1, "(nil)", 5));

	ptr = (unsigned long)p;
	if (write(1, "0x", 2) != 2)
		return (-1);
	len = 0;
	while (ptr)
	{
		buffer[len++] =  base[ptr % 16];
		ptr /= 16;
	}
	i = len - 1;
	while (i >= 0)
		{
			if (write(1, &buffer[i--], 1) != 1)
				return (-1);
		}
	return (len + 2);
}
//////////////////////
#include <stdlib.h>
static	size_t	get_lenth(long n);
static	char	*convert_int(char *str, long n, size_t len, size_t sign);

static	int	itoa(int i)
{
	char	*str;
	size_t	sign;
	size_t	len;
	long	num;
	int		printed;

	sign = 0;
	num = i;
	if (i < 0)
	{
		sign = 1;
		num = - num;
	}
	len = get_lenth(num);
	str = malloc((len + sign + 1) * sizeof(char));
	if (!str)
		return (-1);
	convert_int(str, num, len, sign);
	printed = putstr(str);
	free(str);
	return (printed);
}

static	size_t	get_lenth(long n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
static	char	*convert_int(char *str, long n, size_t len, size_t sign)
{
	str[len + sign] = '\0';
	while (len-- > 0)
	{
		str[len + sign] = (n % 10) + '0';
		n /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
///////////////////////////
#include <stdlib.h>
static	size_t	get_lenth_unsigned(unsigned n);
static	char	*convert_unsigned(char *str, unsigned n, size_t len);

static	int	utoa(unsigned u)
{
	char	*str;
	size_t	len;
	int		printed;

	len = get_lenth_unsigned(u);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (-1);
	convert_unsigned(str, u, len);
	printed = putstr(str);
	free(str);
	return (printed);
}

static	size_t	get_lenth_unsigned(unsigned n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
static	char	*convert_unsigned(char *str, unsigned n, size_t len)
{
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
/////////////////////////////

static	int	print_hex(unsigned u, int uppercase)
{
	int		i;
	int		len;
	char	*base;
	char	buffer[8];

	if (u == 0)
		return (write(1, "0", 1));
	if (uppercase == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";

	i = 0;
	while (u)
	{
		buffer[i++] =  base[u % 16];
		u /= 16;
	}
	len = i;
	while (i--)
		{
			if (write(1, &buffer[i], 1) != 1)
				return (-1);
		}
	return (len);
}