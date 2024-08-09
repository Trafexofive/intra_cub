/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 03:29:36 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/06 03:52:05 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_color(char *buffer, char *delim, int *fill)
{
	char	**res;
	char	*b;
	int		i;
	int		tmp[3];

	b = ft_strtrim(buffer, delim);
	res = ft_split(b, ",");
	if (size_double(res) != 3)
		write_fd("Error\ncolor format not valid\n", 2);
	tmp[0] = ft_atoi(res[0]);
	tmp[1] = ft_atoi(res[1]);
	tmp[2] = ft_atoi(res[2]);
	i = 0;
	while (i < 3)
	{
		if (tmp[i] < 0 || tmp[i] > 255)
			write_fd("Error\ncolor limit exeeded\n", 2);
		i++;
	}
	*fill = (tmp[0] << 16) | (tmp[1] << 8) | tmp[2];
}

void	extract_color(t_data **data_map_adr, t_map **all_map_adr)
{
	t_data	*data_map;
	t_map	*all_map;

	data_map = *data_map_adr;
	all_map = *all_map_adr;
	get_color(all_map->color_c, " C", &data_map->color_c);
	get_color(all_map->color_f, " F", &data_map->color_f);
}

void	assign_textures(t_data **data_map_adr, t_map **all_map_adr)
{
	t_data	*data_map;
	t_map	*all_map;

	data_map = *data_map_adr;
	all_map = *all_map_adr;
	data_map->no_tex = ft_strtrim(all_map->no_tex, " NO");
	data_map->so_tex = ft_strtrim(all_map->so_tex, " SO");
	data_map->we_tex = ft_strtrim(all_map->we_tex, " WE");
	data_map->ea_tex = ft_strtrim(all_map->ea_tex, " EA");
}

void	check_spaces(char **map)
{
	char	**z;
	int		i;
	int		j;

	z = alter_map(map);
	i = 1;
	while (i < size_double(z) - 1)
	{
		j = 1;
		while (z[i][j] && j < ft_strlen(z[i]) - 2)
		{
			if (z[i][j] == '0')
			{
				check_chars(z[i][j + 1], z[i][j - 1],
					z[i + 1][j], z[i - 1][j]);
			}
			if (z[i][j] == ' ')
			{
				check_chars_g(z[i][j + 1], z[i][j - 1],
					z[i + 1][j], z[i - 1][j]);
			}
			j++;
		}
		i++;
	}
}

t_data	*transform(t_map **all_map_adr, t_mlx **ini_adr)
{
	t_data	*tr_map;
	t_map	*all_map;
	t_node	*map;
	int		size;
	int		i;

	all_map = *all_map_adr;
	map = all_map->map;
	size = ft_lst_size(map);
	tr_map = gb_malloc(sizeof(t_data), 0);
	tr_map->ini = *ini_adr;
	tr_map->map = gb_malloc(sizeof(char *) * size + 1, 0);
	assign_textures(&tr_map, all_map_adr);
	i = 0;
	while (map)
	{
		tr_map->map[i++] = map->content;
		map = map->next;
	}
	tr_map->map[i] = NULL;
	extract_color(&tr_map, &all_map);
	check_spaces(tr_map->map);
	return (tr_map);
}
