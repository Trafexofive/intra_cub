/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 08:16:30 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 08:59:57 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/defines.h"
#include "inc/macros.h"
#include "inc/raycast.h"
#include "inc/struct.h"
#include "inc/utils.h"
#include <mlx.h>
#include <stdlib.h>

void	free_all(t_info *info)
{
	void	*mlx;
	void	*mlx_win;

	mlx = info->mlx->mlx;
	mlx_win = info->mlx->mlx_win;
	mlx_destroy_window(mlx, mlx_win);
	exit(0);
}

void	key_hook(int key, t_info *info)
{
	if (key == ESC_KEY)
		free_all(info);
	else
	{
		handle_player_movement(info, key);
	}
}

void	new_image(t_info *info)
{
	info->img.addr = mlx_new_image(info->mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
}
