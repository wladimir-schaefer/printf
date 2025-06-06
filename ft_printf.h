/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:06:13 by wschafer          #+#    #+#             */
/*   Updated: 2025/06/06 14:06:17 by wschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(const char *format, ...);
int	print_str(const char *s);
int	print_char(int i);
int	print_pointer(void *p);
int	print_nbr(int i);
int	print_unsigned(unsigned int u);
int	print_hex(unsigned int u, int uppercase);

#endif