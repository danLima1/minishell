/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:38:13 by dde-lima          #+#    #+#             */
/*   Updated: 2024/10/08 19:12:43 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*dst;
	size_t		i;
	size_t		j;

	i = start;
	j = 0;
	if (i >= ft_strlen(s))
		len = 0;
	dst = (char *)malloc(sizeof(char) * (len)+ 1);
	if (dst == NULL)
		return (NULL);
	while (j < len && s[i] != '\0')
	{
		dst[j] = s[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dst);
}
