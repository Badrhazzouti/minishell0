/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_3_linked_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhazzout <bhazzout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:38:21 by bhazzout          #+#    #+#             */
/*   Updated: 2023/04/13 20:31:00 by bhazzout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *name, char *value, t_env *new)
{
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->env_name = name;
	new->env_value = value;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*lastnode;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		lastnode = *lst;
		while (lastnode->next != NULL)
				lastnode = lastnode->next;
			lastnode->next = new;
	}
}
