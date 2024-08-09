/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:40:13 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/04 12:39:29 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	checker(t_map **all_map_adr)
{
	t_map	*all_map;

	all_map = *all_map_adr;
	if (!all_map->no_tex || !all_map->so_tex
		|| !all_map->we_tex || !all_map->ea_tex
		|| !all_map->color_c || !all_map->color_f)
	{
		return (1);
	}
	return (0);
}

void	check_line(char *g, int mode)
{
	int		i;
	char	*buffer;

	buffer = ft_strtrim(g, " \t");
	i = 0;
	if (mode == 0)
	{
		while (buffer[i])
		{
			if (buffer[i] != '1' && buffer[i] != ' ')
				write_fd("Error\nerror in border\n", 2);
			i++;
		}
	}
	else if (mode == 1)
	{
		if (buffer[0] != '1' || buffer[ft_strlen(buffer) - 1] != '1')
			write_fd("Error\nerror in border\n", 2);
	}
}

void	borders(t_map **all_map_adr)
{
	t_node	*map_list;
	t_map	*map;
	int		list_size;
	int		i;

	map = *all_map_adr;
	map_list = map->map;
	list_size = ft_lst_size(map_list);
	i = 0;
	while (map_list)
	{
		if (i == 0 || i == list_size - 1)
			check_line(map_list->content, 0);
		else
			check_line(map_list->content, 1);
		i++;
		map_list = map_list->next;
	}
}

void	elements(t_map **all_map_adr)
{
	t_node	*map_list;
	t_map	*map;
	char	*content;
	int		i;
	int		players;

	map = *all_map_adr;
	map_list = map->map;
	players = 0;
	while (map_list)
	{
		content = map_list->content;
		i = 0;
		while (content[i])
		{
			if (!ft_strchr(" 10NSWE", content[i]))
				write_fd("Error\ninvalid character\n", 2);
			if (ft_strchr("NSWE", content[i]))
				players++;
			i++;
		}
		map_list = map_list->next;
	}
	if (players != 1)
		write_fd("Error\nno or too many players\n", 2);
}

void	validate(t_map **all_map_adr)
{
	if (checker(all_map_adr) == 1)
		write_fd("Error\ntextures not provided\n", 2);
	borders(all_map_adr);
	elements(all_map_adr);
}
