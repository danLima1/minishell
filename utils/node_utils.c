 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldos_sa2 <ldos-sa2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:50:10 by ldos_sa2          #+#    #+#             */
/*   Updated: 2025/10/06 21:29:40 by ldos_sa2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*newnode(char *v, t_token_type type)
{
	t_token	*new_node;
	char	*value;

	value = ft_strdup(v);
	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

t_token	*node_last(t_token *node)
{
	t_token	*temp;

	if (!node)
		return (NULL);
	temp = node;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	nodeadd_back(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		node_last(*lst)->next = new;
	else
		*lst = new;
}

void	free_nodelist(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}
