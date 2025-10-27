/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:50:17 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/26 19:39:00 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir_list(t_redir *redir_list)
{
	t_redir	*tmp;

	while (redir_list)
	{
		tmp = redir_list->next;
		if (redir_list->file)
			free(redir_list->file);
		free(redir_list);
		redir_list = tmp;
	}
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	int		i;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		if (cmd_list->args)
		{
			i = 0;
			while (cmd_list->args[i])
			{
				free(cmd_list->args[i]);
				i++;
			}
			free(cmd_list->args);
		}
		if (cmd_list->redirs)
			free_redir_list(cmd_list->redirs);
		free(cmd_list);
		cmd_list = tmp;
	}
}

void	print_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	int		i;

	current = cmd_list;
	while (current)
	{
		ft_printf("Command: ");
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				ft_printf("'%s' ", current->args[i]);
				i++;
			}
		}
		ft_printf("\n");
		current = current->next;
	}
}

int	count_commands(t_cmd *cmd)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd;
	if (current->args)
	{
		while (current->args[count])
			count++;
	}
	return (count);
}

t_cmd	*create_cmd(void)
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
