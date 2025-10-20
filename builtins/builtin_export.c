/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/01/15 10:00:00 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}

static int	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new_env;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (1);
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = *env;
	*env = new_env;
	return (0);
}

int	builtin_export(char **args, t_env **env)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	int		i;

	if (!args[1])
	{
		print_export_env(*env);
		return (0);
	}
	
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			key = args[i];
			value = equal_sign + 1;
			add_or_update_env(env, key, value);
			*equal_sign = '=';
		}
		else
		{
			add_or_update_env(env, args[i], "");
		}
		i++;
	}
	return (0);
}