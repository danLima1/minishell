/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/01/15 10:00:00 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(char **args, t_env **env)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	if (!args[1])
		return (0);
	
	i = 1;
	while (args[i])
	{
		current = *env;
		prev = NULL;
		
		while (current)
		{
			if (ft_strcmp(current->key, args[i]) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					*env = current->next;
				
				free(current->key);
				free(current->value);
				free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}