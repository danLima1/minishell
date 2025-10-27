/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 01:43:13 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/27 02:05:33 by dde-lima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_delimiter(char *line, char *delimiter, size_t delim_len)
{
	if (ft_strncmp(line, delimiter, delim_len) == 0
		&& line[delim_len] == '\0')
		return (1);
	return (0);
}

static int	read_heredoc_lines(int write_fd, char *delimiter)
{
	char	*line;
	size_t	delim_len;

	delim_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("minishell: warning: here-document delimited by EOF\n");
			break ;
		}
		if (check_delimiter(line, delimiter, delim_len))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell");
		return (1);
	}
	read_heredoc_lines(pipe_fd[1], delimiter);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}

