/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_entry.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:01:12 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/09 21:22:05 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse/cub.h"
#include "../inc/macros.h"

void	check_extention(char *buffer, char *ext)
{
	int	size_ext;
	int	size;

	size = ft_strlen(buffer) - 1;
	size_ext = ft_strlen(ext) - 1;
	if (size_ext >= size)
		write_fd("Error\nfile name error\n", 2);
	while (ext[size_ext] == buffer[size])
	{
		size_ext--;
		size--;
	}
	if (size_ext != -1)
		write_fd("Error\nfile name error\n", 2);
}

t_data	*parse_entry(int ac, char **av)
{
	t_map	*map;
	t_data	*map_data;
	t_mlx	*ini;

	if (ac != 2)
		write_fd("Error\nerror args\n", 2);
	check_extention(av[1], ".cub");
	ini = gb_malloc(sizeof(t_mlx), 0);
	ini->mlx = mlx_init();
	if (!ini->mlx)
		write_fd("Error\nerror mlx init\n", 2);
	ini->mlx_win = mlx_new_window(ini->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	if (!ini->mlx_win)
		write_fd("Error\nerror mlx window\n", 2);
	map = parse(av[1]);
	validate(&map);
	map_data = transform(&map, &ini);
	//check_textures(&map_data);
	//open_textures(&map_data);
	assign_player_pos(&map_data);
	return (map_data);
}
//
// int	main(int ac, char **av)
// {
// 	t_data	*map_data;
// 	int		i;
// 	char	**gg;
//
// 	map_data = parse_entry(ac, av);
// 	printf("%s\n", map_data->no_tex);
// 	printf("%s\n", map_data->so_tex);
// 	printf("%s\n", map_data->ea_tex);
// 	printf("%s\n", map_data->we_tex);
// 	printf("%X\n", map_data->color_c);
// 	printf("%X\n", map_data->color_f);
// 	gg = map_data->map;
// 	i = 0;
// 	while (gg[i])
// 	{
// 		printf("%s\n", gg[i]);
// 		i++;
// 	}
// 	printf("%d %d\n", map_data->no_texture->w, map_data->no_texture->h);
// 	printf("%d %d\n", map_data->so_texture->w, map_data->so_texture->h);
// 	printf("%d %d\n", map_data->ea_texture->w, map_data->ea_texture->h);
// 	printf("%d %d\n", map_data->we_texture->w, map_data->we_texture->h);
// 	printf("player x = %d\nplayer y = %d\nplayer_face = %c\n", map_data->player_x, map_data->player_y, map_data->player_face);
// 	return (0);
// }
