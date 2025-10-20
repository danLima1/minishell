/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/01/15 10:00:00 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char **args, t_env *env)
{
	char	*path;
	char	*home;
	t_env	*current;

	if (!args[1])
	{
		current = env;
		while (current)
		{
			if (ft_strcmp(current->key, "HOME") == 0)
			{
				home = current->value;
				break ;
			}
			current = current->next;
		}
		if (!current || !home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		path = home;
	}
	else
		path = args[1];
	
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}