/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:40:01 by ldos-sa2          #+#    #+#             */
/*   Updated: 2025/10/27 10:20:52 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_redir_to_cmd(t_cmd *cmd, t_token_type type, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	new_redir->eof = NULL;
	new_redir->eof = NULL;
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		current = cmd->redirs;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

static void	add_eof_to_cmd(t_cmd *cmd, t_token_type type, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = NULL;
	new_redir->eof = ft_strdup(file);
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		current = cmd->redirs;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

t_token	*handle_redd_arg(t_cmd *current_cmd, t_token *t)
{
	if (t->type == TOKEN_REDIR_IN || t->type == TOKEN_REDIR_OUT
		|| t->type == TOKEN_REDIR_APPEND)
	{
		if (t->next && t->next->type == TOKEN_WORD)
		{
			add_redir_to_cmd(current_cmd, t->type, t->next->value);
			return (t->next);
		}
	}
	else if (t->type == TOKEN_HEREDOC)
	{
		if (t->next && t->next->type == TOKEN_WORD)
		{
			add_eof_to_cmd(current_cmd, t->type, t->next->value);
			return (t->next);
		}
	}
	return (t);
}
