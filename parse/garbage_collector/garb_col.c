/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_col.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:44:19 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 16:41:04 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/garbage.h"

void	*gb_malloc(size_t size, int type)
{
	static void		*all[MAX_SIZE];
	static int		i = 0;
	void			*addr;

	if (type == 1)
	{
		while (--i >= 0)
			free(all[i]);
	}
	else if (type == 0)
	{
		addr = malloc(size);
		if (!addr)
		{
			while (i--)
				free(all[i]);
			write(2, "Error\nmalloc error !\n", 22);
			exit (1);
		}
		i++;
		all[i] = addr;
		return (addr);
	}
	return (NULL);
}
