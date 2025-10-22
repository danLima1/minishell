/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:27:24 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/22 06:09:18 by ldos_sa2         ###   ########.fr       */
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
