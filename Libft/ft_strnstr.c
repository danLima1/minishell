/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:41:06 by dde-lima          #+#    #+#             */
/*   Updated: 2024/10/08 17:41:32 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (!*little || big == little)
		return ((char *) big);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[j])
		{
			while ((big[i + j] == little[j]) && (i + j) < len)
			{
				j++;
			}
			if (little[j] == '\0')
				return ((char *)(&big[i]));
			j = 0;
		}
		i++;
	}
	return (NULL);
}
