/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_handles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:43:10 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/22 09:48:38 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_parent_process(int prev_fd, int *pp_fd, t_cmd *crnt)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (crnt->next)
		close(pp_fd[1]);
	return (0);
}

int	handle_fork_process(t_cmd *crnt, t_shell *shell, int *pp_fd, int prev_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_pipes(prev_fd, pp_fd, crnt);
		execute_child_process(crnt, shell);
	}
	else if (pid > 0)
		return (handle_parent_process(prev_fd, pp_fd, crnt));
	else
	{
		perror("fork");
		return (1);
	}
	return (0);
}
