/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:54:39 by dde-lima          #+#    #+#             */
/*   Updated: 2024/10/04 13:29:36 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dst;
	size_t	i;
	char	*csrc;

	csrc = (char *) src;
	dst = (char *) dest;
	i = 0;
	while (i < n)
	{
		dst[i] = csrc[i];
		i++;
	}
	return (dst);
}

/*int main()
{
	char dst[] = "hello world";
	char src[] = "ana";
	ft_memcpy(dst, src, 3);
	#include <stdio.h>
	printf("%s", dst);
}*/
