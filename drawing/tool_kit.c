/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_kit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:08:47 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/11 20:24:02 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"
#include <math.h>
#include <mlx.h>

bool	put_pixel(t_img *data, t_point pixel, int color)
{
	char	*dst;
	int		x;
	int		y;

	y = pixel.y;
	x = pixel.x;
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
	else
		return (false);
	return (true);
}

void	clear_window(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->mlx_win);
}
