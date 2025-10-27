/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:18:07 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/27 03:05:09 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redir(char *token)
{
	if (!ft_strncmp(token, ">", 1) || !ft_strncmp(token, "<", 1))
		return (1);
	else if (!ft_strncmp(token, ">>", 2) || !ft_strncmp(token, "<<", 2))
		return (1);
	else
		return (0);
}

static int	is_quoted(char *token)
{
	if (!ft_strncmp(token, "\"", 1) || !ft_strncmp(token, "'", 1))
		return (1);
	else
		return (0);
}

static void	add_redir_token(char *token, t_token **ls)
{
	t_token	*node;

	if (!ft_strncmp(token, "<<", 2))
	{
		node = newnode(token, TOKEN_HEREDOC);
		nodeadd_back(ls, node);
	}
	else if (!ft_strncmp(token, ">>", 2))
	{
		node = newnode(token, TOKEN_REDIR_APPEND);
		nodeadd_back(ls, node);
	}
	else if (!ft_strncmp(token, "<", 1))
	{
		node = newnode(token, TOKEN_REDIR_IN);
		nodeadd_back(ls, node);
	}
	else if (!ft_strncmp(token, ">", 1))
	{
		node = newnode(token, TOKEN_REDIR_OUT);
		nodeadd_back(ls, node);
	}
}

static t_token	*create_token_list(char **token_array)
{
	t_token	*tokens;
	t_token	*node;
	int		i;

	tokens = NULL;
	i = 0;
	while (token_array[i])
	{
		if (!ft_strncmp(token_array[i], "|", 1))
			add_pipe_token(token_array[i], &tokens);
		else if (is_quoted(token_array[i]))
			add_quoted_token(token_array[i], &tokens);
		else if (is_redir(token_array[i]))
			add_redir_token(token_array[i], &tokens);
		else
		{
			node = newnode(token_array[i], TOKEN_WORD);
			nodeadd_back(&tokens, node);
		}
		free(token_array[i]);
		i++;
	}
	return (tokens);
}

t_token	*lexer_tokenize(char *input)
{
	char	**token_array;
	t_token	*tokens;
	int		num_tokens;

	if (!input || !*input)
		return (NULL);
	num_tokens = count_words(input);
	if (num_tokens == 0)
		return (NULL);
	token_array = ms_split(input);
	if (!token_array)
		return (NULL);
	tokens = create_token_list(token_array);
	free(token_array);
	return (tokens);
}
