/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:01:08 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/04 15:27:12 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	assigner(char *buffer, t_map **all_map_adr)
{
	t_map	*all_map;

	if (!buffer)
		return ;
	all_map = *all_map_adr;
	while (*buffer == ' ' || *buffer == '\t' || *buffer == '\n')
		buffer++;
	if (ft_strncmp(buffer, "NO ", 3) == 0 && check(all_map->no_tex))
		all_map->no_tex = trim_behind(buffer);
	if (ft_strncmp(buffer, "SO ", 3) == 0 && check(all_map->so_tex))
		all_map->so_tex = trim_behind(buffer);
	if (ft_strncmp(buffer, "WE ", 3) == 0 && check(all_map->we_tex))
		all_map->we_tex = trim_behind(buffer);
	if (ft_strncmp(buffer, "EA ", 3) == 0 && check(all_map->ea_tex))
		all_map->ea_tex = trim_behind(buffer);
	if (ft_strncmp(buffer, "F ", 2) == 0 && check(all_map->color_f))
		all_map->color_f = trim_behind(buffer);
	if (ft_strncmp(buffer, "C ", 2) == 0 && check(all_map->color_c))
		all_map->color_c = trim_behind(buffer);
}

// last map in good is not working !!

int	move_to_map(char *buffer)
{
	while (*buffer == ' ' || *buffer == '\t')
		buffer++;
	if (*buffer == '0' || *buffer == '1')
		return (1);
	return (0);
}

void	init(t_map **all_map_adr)
{
	t_map	*all_map;

	all_map = *all_map_adr;
	all_map->ea_tex = NULL;
	all_map->no_tex = NULL;
	all_map->so_tex = NULL;
	all_map->we_tex = NULL;
	all_map->color_c = NULL;
	all_map->color_f = NULL;
	all_map->map = NULL;
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		write_fd("Error\nerror openning map", 2);
	return (fd);
}

t_map	*parse(char *map)
{
	t_map	*all_map;
	char	*buffer;
	t_node	*map_list;
	int		fd;

	fd = open_file(map);
	map_list = NULL;
	all_map = gb_malloc(sizeof(t_map), 0);
	init(&all_map);
	while (true)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		assigner(buffer, &all_map);
		if (move_to_map(buffer) == 1 && checker(&all_map) == 1)
			write_fd("Error\nmisplaced map\n", 2);
		else if (move_to_map(buffer) == 0 && map_list != NULL)
			write_fd("Error\nempty line in map\n", 2);
		else if (move_to_map(buffer) == 1 && checker(&all_map) == 0)
			ft_lstadd_back(&map_list, ft_lstnew(trim_behind(buffer)));
	}
	close(fd);
	all_map->map = map_list;
	return (all_map);
}
