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

void	ft_putstr_fd(char *s, int fd);
static	size_t	get_lenth(long n);
static	char	*convert(char *str, long n, size_t i, size_t sign);

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i = 0;
	char	*str;
	unsigned int	j;


	va_start(args, s);
	
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s == 'c')
			{
				i = va_arg(args, int);
				write(1, &i, 1);
			}
			if (*s == 's')
			{
				str = va_arg(args, char*);
				ft_putstr_fd(str, 1);
			}
			if (*s == 'p')
			{
				j = va_arg(args, unsigned int);
				get_lenth(j);

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

	//ft_printf("www %s mmm", str);
	printf("%x\n", 123);
}


void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
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

static	char	*convert(char *str, unsigned int n, size_t i, size_t flag)
{
	str[i] = '\0';
	while (i--)
	{
		char *base = "123456789ABCDEF";
		str[i] = n % 16 + '0';
		n = n / 10;
	}
	
	str[0] = '-';
	return (str);
}