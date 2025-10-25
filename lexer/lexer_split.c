/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:36:27 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/06 21:40:31 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words(char const *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] == '"' || s[i] == '\'')
		{
			if (handle_q(s, &i) == -1)
				return (-1);
		}
		else if (s[i] == '>' || s[i] == '<' || s[i] == '|')
			handle_redd(s, &i);
		else
			skip_words(s, &i);
		words++;
	}
	return (words);
}

static char	*copy_tokens(const char *s, int *i)
{
	char	*token;
	char	q;
	int		start;

	if (s[*i] == '"' || s[*i] == '\'')
	{
		q = s[*i];
		(*i)++;
		start = *i;
		while (s[*i] && s[*i] != q)
			(*i)++;
		token = ft_substr(s, start, *i - start);
		if (s[*i] == q)
			(*i)++;
	}
	else
	{
		start = *i;
		while (s[*i] && s[*i] != ' ' && s[*i] != '|' && s[*i] != '<' 
			&& s[*i] != '>')
			(*i)++;
		token = ft_substr(s, start, *i - start);
	}
	return (token);
}

static char	*copy_notwords(const char *s, int *i)
{
	char	*token;
	char	q;
	int		start;

	start = *i;
	if (s[*i] == '|')
	{
		token = ft_substr(s, start, 1);
		(*i)++;
	}
	else if (s[*i] == '>' || s[*i] == '<')
	{
		q = s[*i];
		(*i)++;
		if (s[*i] == q)
			(*i)++;
		token = ft_substr(s, start, *i - start);
	}
	return (token);
}

char	**ms_split(char const *s)
{
	int		i;
	int		j;
	int		num_tokens;
	char	**tokens;

	i = 0;
	j = 0;
	num_tokens = count_words(s);
	if (num_tokens == -1)
		return (NULL);
	tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break;
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			tokens[j++] = copy_notwords(s, &i);
		else if (s[i])
			tokens[j++] = copy_tokens(s, &i);
	}
	tokens[j] = NULL;
	return (tokens);
}
