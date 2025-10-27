/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 01:43:27 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/26 22:17:18 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token: '%s', Type: %d\n", current->value, current->type);
		current = current->next;
	}
}

int	validate_tokens(t_token *tokens)
{
	t_token	*current;
	int		pipe_count;

	if (!tokens)
		return (0);
	current = tokens;
	pipe_count = 0;
	if (current->type == TOKEN_PIPE)
		return (0);
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			pipe_count++;
			if (!current->next || current->next->type == TOKEN_PIPE)
				return (0);
		}
		current = current->next;
	}
	if (current && current->type == TOKEN_PIPE)
		return (0);
	return (1);
}
