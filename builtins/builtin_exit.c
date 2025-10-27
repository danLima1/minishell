/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:01:04 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/26 22:48:31 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_env *env)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1])
	{
		free_env(env);
		exit(0);
	}
	if (!is_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		free_env(env);
		exit(2);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	free_env(env);
	exit(exit_code);
}
