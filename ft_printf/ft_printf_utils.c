/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:47:33 by dde-lima          #+#    #+#             */
/*   Updated: 2024/10/23 09:00:47 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr("(null)"));
	while (s[i] != '\0')
		write(1, &s[i++], 1);
	return (i);
}

int	ft_putnbr(int n)
{
	long	num;
	int		count;

	count = 0;
	num = n;
	if (num < 0)
	{
		count += ft_putchar('-');
		num = -num;
	}
	if (num < 10)
		count += ft_putchar(num + '0');
	else
	{
		count += ft_putnbr(num / 10);
		count += ft_putchar((num % 10) + '0');
	}
	return (count);
}

int	printhex(unsigned long int nbr, unsigned int base, char *xcase)
{
	int	count;

	count = 0;
	if (nbr >= 16)
		count += printhex(nbr / base, base, xcase);
	count += ft_putchar(xcase[nbr % base]);
	return (count);
}

int	ft_u_putnbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n < 10)
		count += ft_putchar(n + '0');
	else
	{
		count += ft_putnbr(n / 10);
		count += ft_putchar((n % 10) + '0');
	}
	return (count);
}
