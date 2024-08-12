/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:21:42 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 18:30:43 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/raycast.h"
#include "../inc/struct.h"
#include "../inc/utils.h"

void	raycaster(t_info *info)
{
	test_cast(info);
}

void	renderer(t_info *info)
{
	t_mlx	*mlx;

	mlx = info->mlx;
	raycaster(info);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, info->img.img, 0, 0);
}
