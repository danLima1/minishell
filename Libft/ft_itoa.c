/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:16:51 by dde-lima          #+#    #+#             */
/*   Updated: 2024/10/07 14:09:43 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_lenght(long int n)
{
	int	lenght;

	lenght = 0;
	if (n < 0)
	{
		lenght++;
		n *= -1;
	}
	while (n > 0)
	{
		lenght++;
		n /= 10;
	}
	return (lenght);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		n_lenght;
	long	nb;

	nb = n;
	n_lenght = get_lenght(nb);
	str = (char *)malloc(sizeof(char) * n_lenght + 1);
	str[n_lenght] = '\0';
	if (n == 0)
		return (ft_strdup("0"));
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[n_lenght -1] = nb % 10 + '0';
		nb /= 10;
		n_lenght--;
	}
	return (str);
}
