/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:22:34 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/26 22:16:45 by ldos-sa2         ###   ########.fr       */
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

static void	process_export_arg(char *arg, t_env **env)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		key = arg;
		value = equal_sign + 1;
		add_or_update_env(env, key, value);
		*equal_sign = '=';
	}
	else
	{
		add_or_update_env(env, arg, "");
	}
}

int	builtin_export(char **args, t_env **env)
{
	int		i;

	if (!args[1])
	{
		print_export_env(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		process_export_arg(args[i], env);
		i++;
	}
	return (0);
}
