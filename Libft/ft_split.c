/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:24:32 by dde-lima          #+#    #+#             */
/*   Updated: 2024/10/08 18:26:09 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *str, char c)
{
	int	reset;
	int	i;

	reset = 0;
	i = 0;
	while (*str)
	{
		if (*str != c && reset == 0)
		{
			reset = 1;
			i++;
		}
		else if (*str == c)
		{
			reset = 0;
		}
		str++;
	}
	return (i);
}

static char	*worddup(char const *str, int start, int end)
{
	int		i;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
		dest[i++] = str[start++];
	dest[i] = '\0';
	return (dest);
}

static int	find_words(char const *str, char c, char **split)
{
	int	i;
	int	count;
	int	len;
	int	j;

	j = 0;
	i = -1;
	count = -1;
	len = ft_strlen(str);
	while (++i <= len)
	{
		if (str[i] != c && count < 0)
			count = i;
		else if ((str[i] == c || i == len) && count >= 0)
		{
			split[j++] = worddup(str, count, i);
			count = -1;
		}
	}
	split[j] = NULL;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!split)
		return (NULL);
	find_words(s, c, split);
	return (split);
}
