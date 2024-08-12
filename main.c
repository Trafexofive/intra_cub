/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 08:06:08 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 18:40:13 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/defines.h"
#include "inc/macros.h"
#include "inc/raycast.h"
#include "inc/struct.h"
#include "inc/utils.h"
#include <mlx.h>
#include <stdlib.h>

int	get_offset(t_img *image, t_point pixel)
{
	int	x;
	int	y;
	int	offset;

	x = pixel.x;
	y = pixel.y;
	x = x % 64;
	y = y % 64;
	offset = (y * image->line_length + x * (image->bits_per_pixel / 8));
	return (offset);
}

bool	game_init(t_info *info)
{
	t_mlx	*mlx;
	t_img	image;

	mlx = info->mlx;
	image.img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (image.img == NULL)
		return (false);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	info->img = image;
	mlx_hook(mlx->mlx_win, 17, 0, (void *)free_all, info);
	mlx_hook(mlx->mlx_win, 2, 1L << 1, (void *)key_hook, info);
	mlx_loop_hook(mlx->mlx, (void *)renderer, info);
	mlx_loop(mlx->mlx);
	return (true);
}

t_info	*vars_init(int ac, char **av)
{
	t_data	*data;
	t_info	*info;

	data = parse_entry(ac, av);
	info = gb_malloc(sizeof(t_info), 0);
	info->data = data;
	info->mlx = data->ini;
	info->map = data->map;
	info->player = player_init();
	return (info);
}

int	main(int ac, char **av)
{
	game_init(vars_init(ac, av));
	return (1);
}
