/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:22:45 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/25 15:24:22 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_input_redir(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output_redir(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_append_redir(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	process_redir(t_redir *redir)
{
	if (redir->type == TOKEN_REDIR_IN)
		return (handle_input_redir(redir->file));
	else if (redir->type == TOKEN_REDIR_OUT)
		return (handle_output_redir(redir->file));
	else if (redir->type == TOKEN_REDIR_APPEND)
		return (handle_append_redir(redir->file));
	else if (redir->type == TOKEN_HEREDOC)
		return (handle_heredoc(redir->eof));
	return (0);
}

int	handle_redirections(t_redir *redirs)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (process_redir(current) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}
