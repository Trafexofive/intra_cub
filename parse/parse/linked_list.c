/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:56:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/03 08:44:40 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_node	*ft_lstnew(void *content)
{
	t_node	*new_node;

	new_node = (t_node *)gb_malloc(sizeof(t_node), 0);
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = ft_lstlast(*lst);
			tmp->next = new;
		}
	}
}

t_node	*ft_lstlast(t_node *lst)
{
	t_node	*p;

	if (!lst)
		return (NULL);
	p = lst;
	while (p->next != NULL)
		p = p->next;
	return (p);
}

int	ft_lst_size(t_node *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
