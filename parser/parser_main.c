/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:08:43 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/22 06:25:55 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	add_arg_to_cmd(t_cmd *cmd, char *arg, t_env *env, int last_exit)
{
	char	**new_args;
	char	*expanded_arg;
	int		count;
	int		i;

	count = count_commands(cmd);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	expanded_arg = expand_string(arg, env, last_exit);
	if (expanded_arg)
		new_args[count] = expanded_arg;
	else
		new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}

static void	add_redir_to_cmd(t_cmd *cmd, t_token_type type, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
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

t_cmd	*parse_tokens(t_token *tokens, t_env *env, int last_exit)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_token	*token;

	if (!tokens)
		return (NULL);
	cmd_list = create_cmd();
	current_cmd = cmd_list;
	token = tokens;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			add_arg_to_cmd(current_cmd, token->value, env, last_exit);
		else if (token->type == TOKEN_PIPE)
		{
			current_cmd->next = create_cmd();
			current_cmd = current_cmd->next;
		}
		else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_HEREDOC)
		{
			if (token->next && token->next->type == TOKEN_WORD)
			{
				add_redir_to_cmd(current_cmd, token->type, token->next->value);
				token = token->next;
			}
		}
		token = token->next;
	}
	return (cmd_list);
}
