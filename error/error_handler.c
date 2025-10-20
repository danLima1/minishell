/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/01/15 10:00:00 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *cmd, char *arg, char *msg)
{
	printf("minishell: ");
	if (cmd)
		printf("%s: ", cmd);
	if (arg)
		printf("%s: ", arg);
	if (msg)
		printf("%s", msg);
	printf("\n");
}

void	syntax_error(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
}

int	handle_malloc_error(void)
{
	printf("minishell: memory allocation failed\n");
	return (1);
}

int	handle_fork_error(void)
{
	perror("minishell: fork");
	return (1);
}