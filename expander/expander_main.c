/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos-sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:46:32 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/27 14:51:12 by ldos-sa2         ###   ########.fr       */
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

static char	*process_var(char *var_name, int *j, t_shell *shell)
{
	char	*var_value;
	char	*result;

	if (!var_name)
		return (NULL);
	var_value = expand_variable(var_name, shell->env, shell->exit_status);
	result = malloc(ft_strlen(var_value) + 1);
	if (var_value)
	{
		ft_strcpy(result + *j, var_value);
		*j += ft_strlen(var_value);
		free(var_value);
	}
	//free(var_name);
	return (result);
}
static int	get_expand_size(char *str, t_shell *shell)
{
	char	*result;
	char	*var_name;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			var_name = get_var_name(str, &i);
			result = expand_variable(var_name, shell->env, shell->exit_status);
			len += ft_strlen(result);
			free(var_name);
			free(result);
		}
		else
		{
			i++;
			len++;
		}
	}
	ft_printf("length: %d\n", len);
	return(len);
}

static char	*init_result_buffer(char *str, t_shell *shell)
{
	char	*result;

	if (!str)
		return (NULL);
	result = (char *)malloc((get_expand_size(str, shell)) + 1);
	return (result);
}



char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
	char	*var_name;
	int		i;
	int		j;

	result = init_result_buffer(str, shell);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			var_name = get_var_name(str, &i);
			result = ft_strdup(process_var(var_name, &j, shell));
			if (process_var(var_name, &j, shell) == NULL)
				return (free(result), NULL);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
