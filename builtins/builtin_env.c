/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:45:19 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/26 16:52:09 by ldos-sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(char **args, t_env *env)
{
	t_env	*current;

	(void)args;
	current = env;
	while (current)
	{
		if (current->value)
			ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
