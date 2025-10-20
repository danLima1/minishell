/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/01/15 10:00:00 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, str + start, len);
	var_name[len] = '\0';
	return (var_name);
}

static char	*expand_variable(char *var_name, t_env *env, int last_exit)
{
	t_env	*current;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(last_exit));
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

static int	process_variable(char *str, int *i, char *result, int *j, t_env *env, int last_exit)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	var_name = get_var_name(str, i);
	if (!var_name)
		return (0);
	var_value = expand_variable(var_name, env, last_exit);
	if (var_value)
	{
		ft_strcpy(result + *j, var_value);
		*j += ft_strlen(var_value);
		free(var_value);
	}
	free(var_name);
	return (1);
}

static char	*init_result_buffer(char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) * 2 + 1);
	return (result);
}

char	*expand_string(char *str, t_env *env, int last_exit)
{
	char	*result;
	int		i;
	int		j;

	result = init_result_buffer(str);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (!process_variable(str, &i, result, &j, env, last_exit))
			{
				free(result);
				return (NULL);
			}
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}