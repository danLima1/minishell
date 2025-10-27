/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:43:19 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/26 16:53:06 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *cmd, char *arg, char *msg)
{
	ft_printf("minishell: ");
	if (cmd)
		ft_printf("%s: ", cmd);
	if (arg)
		ft_printf("%s: ", arg);
	if (msg)
		ft_printf("%s", msg);
	ft_printf("\n");
}

void	syntax_error(char *token)
{
	ft_printf("minishell: syntax error near unexpected token `%s'\n", token);
}

int	handle_malloc_error(void)
{
	ft_printf("minishell: memory allocation failed\n");
	return (1);
}

int	handle_fork_error(void)
{
	perror("minishell: fork");
	return (1);
}
