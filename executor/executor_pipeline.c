/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:44:52 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/25 15:20:05 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_parent_process(int prev_fd, int *pipe_fd, t_cmd *current)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (current->next)
		close(pipe_fd[1]);
	return (0);
}

static int	h_fork_p(t_cmd *current, t_shell *shell, int *pipe_fd, int prev_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_pipes(prev_fd, pipe_fd, current);
		execute_child_process(current, shell);
	}
	else if (pid > 0)
		return (handle_parent_process(prev_fd, pipe_fd, current));
	else
	{
		perror("fork");
		return (1);
	}
	return (0);
}

static int	process_pipe_cmd(t_cmd *current, t_shell *shell, int *prev_fd)
{
	int		pipe_fd[2];
	int		old_prev_fd;

	old_prev_fd = *prev_fd;
	if (current->next && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	if (current->next)
		*prev_fd = pipe_fd[0];
	return (h_fork_p(current, shell, pipe_fd, old_prev_fd));
}

static int	wait_for_all_processes(t_cmd *cmd_list)
{
	int		status;
	t_cmd	*current;
	int		last_status;

	current = cmd_list;
	last_status = 0;
	while (current)
	{
		wait(&status);
		last_status = WEXITSTATUS(status);
		current = current->next;
	}
	return (last_status);
}

int	execute_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	int		prev_fd;
	t_cmd	*current;

	prev_fd = -1;
	current = cmd_list;
	while (current)
	{
		if (process_pipe_cmd(current, shell, &prev_fd) != 0)
			return (1);
		current = current->next;
	}
	return (wait_for_all_processes(cmd_list));
}
