/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/01/15 10:00:00 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_child_pipes(int prev_fd, int *pipe_fd, t_cmd *current)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

static void	execute_child_process(t_cmd *current, t_shell *shell)
{
	char	*executable;

	if (handle_redirections(current->redirs) != 0)
		exit(1);
	if (is_builtin(current->args[0]))
		exit(execute_builtin(current->args, shell));
	else
	{
		executable = find_executable(current->args[0], shell->env);
		if (execve(executable, current->args, NULL) == -1)
		{
			perror("minishell");
			exit(127);
		}
	}
}

static int	handle_parent_process(int prev_fd, int *pipe_fd, t_cmd *current)
{
	int	status;

	if (prev_fd != -1)
		close(prev_fd);
	if (current->next)
		close(pipe_fd[1]);
	wait(&status);
	return (WEXITSTATUS(status));
}

static int	process_pipeline_command(t_cmd *current, t_shell *shell, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (current->next && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		setup_child_pipes(*prev_fd, pipe_fd, current);
		execute_child_process(current, shell);
	}
	else if (pid > 0)
	{
		if (current->next)
			*prev_fd = pipe_fd[0];
		return (handle_parent_process(*prev_fd, pipe_fd, current));
	}
	else
	{
		perror("fork");
		return (1);
	}
	return (0);
}

int	execute_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	int		prev_fd;
	t_cmd	*current;
	int		last_status;

	prev_fd = -1;
	current = cmd_list;
	last_status = 0;
	while (current)
	{
		last_status = process_pipeline_command(current, shell, &prev_fd);
		if (last_status != 0)
			return (last_status);
		current = current->next;
	}
	return (last_status);
}