/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-lima <dde-lima@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:46:32 by dde-lima          #+#    #+#             */
/*   Updated: 2025/10/27 15:44:56 by dde-lima         ###   ########.fr       */
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

static void	process_var(char *var_name, char *result, int *j, t_shell *shell)
{
	char	*var_value;
	int len;

	if (!var_name || !result)
		return ;
	var_value = expand_variable(var_name, shell->env, shell->exit_status);
	if (var_value)
	{
		len = ft_strlen(var_value);
		ft_strcpy(result + *j, var_value);
		*j += len;
		free(var_value);
	}
	free(var_name);
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
			process_var(var_name, result, &j, shell);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
