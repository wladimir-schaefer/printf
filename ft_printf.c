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
static	int print_decimal(int i);

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i = 0;
	char	*str;
	void	*p;


	va_start(args, s);
	
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s == 'c')
			{
				i = va_arg(args, int);
				putchar(i);
			}
			if (*s == 's')
			{
				str = va_arg(args, char*);
				putstr(str);
			}
			if (*s == 'p')
			{
				p = va_arg(args, void *);
				print_pointer(p);

			}
		}
		else
		{
			write(1, s, 1);			
		}
		s++;
	}

	va_end(args);
	return(i);
}

#include <stdio.h>
int	main()
{
//	char *str = "abcdef";
	int i = 125;

	printf("%d\n",ft_printf("www %p mmm\n", i));
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

static	int print_decimal(int i)
{

}