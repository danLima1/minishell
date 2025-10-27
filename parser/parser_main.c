/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:08:43 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/26 22:12:53 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_expanded_arg(char *arg, t_shell *shell)
{
	char	*expanded_arg;

	expanded_arg = expand_string(arg, shell);
	if (expanded_arg)
		return (expanded_arg);
	return (ft_strdup(arg));
}

static void	add_arg_to_cmd(t_cmd *cmd, char *arg, t_shell *shell)
{
	char	**new_args;
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
	new_args[count] = get_expanded_arg(arg, shell);
	new_args[count + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}

static void	token_arg(t_token *t, t_shell *shell, t_cmd *current_cmd)
{
	while (t)
	{
		if (t->type == TOKEN_WORD)
			add_arg_to_cmd(current_cmd, t->value, shell);
		else if (t->type == TOKEN_PIPE)
		{
			current_cmd->next = create_cmd();
			current_cmd = current_cmd->next;
		}
		else if (t->type == TOKEN_REDIR_IN || t->type == TOKEN_REDIR_OUT
			|| t->type == TOKEN_REDIR_APPEND || t->type == TOKEN_HEREDOC)
			t = handle_redd_arg(current_cmd, t);
		t = t->next;
	}
}

t_cmd	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_token	*t;

	if (!tokens)
		return (NULL);
	cmd_list = create_cmd();
	current_cmd = cmd_list;
	t = tokens;
	token_arg(t, shell, current_cmd);
	return (cmd_list);
}
