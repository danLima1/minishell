/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:33:41 by dde-lima          #+#    #+#             */
/*   Updated: 2024/10/04 14:16:49 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*cast;

	cast = (char *)s;
	i = 0;
	while (i < n)
	{
		cast[i] = c;
		i++;
	}
	return (s);
}

/*int main()
{
	int s[] = {0, 1, 2, 3,4};
	ft_memset(s, 9, 1);
	#include <stdio.h>
	printf("%d", s[0]);
}*/
