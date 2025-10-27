/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 00:00:00 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/27 03:07:17 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}

static char	*join_env_pair(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

char	**env_to_array(t_env *env)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (count_env_vars(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			envp[i] = join_env_pair(env->key, env->value);
			if (!envp[i])
				return (NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_env_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
