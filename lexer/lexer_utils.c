/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:27:24 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/27 03:05:33 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_words(const char *s, int *i)
{
	while (s[*i] && s[*i] != ' ' && s[*i] != '|'
		&& s[*i] != '<' && s[*i] != '>')
		(*i)++;
}

void	handle_redd(const char *s, int *i)
{
	char	c;

	if (s[*i] == '|')
		(*i)++;
	c = s[*i];
	(*i)++;
	if (s[*i] == c)
		(*i)++;
}

int	handle_q(const char *s, int *i)
{
	char	q;

	q = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != q)
		(*i)++;
	if (!s[*i])
		return (-1);
	(*i)++;
	return (1);
}

void	add_quoted_token(char *token, t_token **ls)
{
	t_token	*node;

	if (token[0] == '\'')
	{
		token = ft_substr(token, 1, ft_strlen(token) - 1);
		node = newnode(token, TOKEN_QUOTED);
		nodeadd_back(ls, node);
	}
	else if (token[0] == '"')
	{
		token = ft_substr(token, 1, ft_strlen(token) - 1);
		node = newnode(token, TOKEN_WORD);
		nodeadd_back(ls, node);
	}
}

void	add_pipe_token(char *token, t_token **ls)
{
	t_token	*node;

	node = newnode(token, TOKEN_PIPE);
	nodeadd_back(ls, node);
}
