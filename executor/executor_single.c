/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/01/15 10:00:00 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	execute_builtin_with_redir(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(cmd->redirs) != 0)
	{
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	result = execute_builtin(cmd->args, shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (result);
}

static int	execute_external_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*executable;

	executable = find_executable(cmd->args[0], shell->env);
	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(cmd->redirs) != 0)
			exit(1);
		if (execve(executable, cmd->args, NULL) == -1)
		{
			perror("minishell");
			exit(127);
		}
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(executable);
		return (WEXITSTATUS(status));
	}
	perror("fork");
	free(executable);
	return (1);
}

int	execute_single_command(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (is_builtin(cmd->args[0]))
	{
		if (cmd->redirs)
			return (execute_builtin_with_redir(cmd, shell));
		return (execute_builtin(cmd->args, shell));
	}
	return (execute_external_command(cmd, shell));
}