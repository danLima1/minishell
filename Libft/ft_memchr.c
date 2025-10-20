/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:02:28 by dde-lima          #+#    #+#             */
/*   Updated: 2024/09/27 13:24:12 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*cs;

	cs = (const unsigned char *)s;
	while (n > 0)
	{
		if (*cs == (unsigned char)c)
			return ((void *)cs);
		n--;
		cs++;
	}
	return (NULL);
}
