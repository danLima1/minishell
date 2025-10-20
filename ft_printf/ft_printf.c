/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:47:31 by dde-lima          #+#    #+#             */
/*   Updated: 2024/10/23 08:56:37 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	arguments_print(char c, va_list args)
{
	int	funct;

	funct = 0;
	if (c == 'c')
		funct = ft_putchar(va_arg(args, int));
	else if (c == 's')
		funct = ft_putstr(va_arg(args, char *));
	else if (c == 'i' || c == 'd')
		funct = ft_putnbr(va_arg(args, int));
	else if (c == '%')
		funct = ft_putchar('%');
	else if (c == 'x')
		funct = printhex(va_arg(args, unsigned int), 16, "0123456789abcdef");
	else if (c == 'u')
		funct = ft_u_putnbr(va_arg(args, unsigned int));
	else if (c == 'X')
		funct = printhex(va_arg(args, unsigned int), 16, "0123456789ABCDEF");
	else if (c == 'p')
		funct = ft_putptr(va_arg(args, unsigned long int));
	return (funct);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	var;
	int		count;

	va_start(var, fmt);
	count = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			count += arguments_print(*(++fmt), var);
		}
		else
			count += ft_putchar((char) *fmt);
		fmt++;
	}
	va_end (var);
	return (count);
}
