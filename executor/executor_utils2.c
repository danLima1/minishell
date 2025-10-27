/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:17:11 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/25 15:17:47 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_child_pipes(int prev_fd, int *pipe_fd, t_cmd *current)
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

void	execute_child_process(t_cmd *current, t_shell *shell)
{
	char	*executable;
	char	**envp;

	if (handle_redirections(current->redirs) != 0)
		exit(1);
	if (is_builtin(current->args[0]))
		exit(execute_builtin(current->args, shell));
	else
	{
		executable = find_executable(current->args[0], shell->env);
		envp = env_to_array(shell->env);
		if (execve(executable, current->args, envp) == -1)
		{
			free_env_array(envp);
			perror("minishell");
			exit(127);
		}
	}
}
