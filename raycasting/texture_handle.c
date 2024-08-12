/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:30:04 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 14:42:42 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/raycast.h"
#include "../inc/struct.h"
#include "../inc/utils.h"
#include <math.h>

t_texture	*get_side_tex(char wall_side, t_data *data)
{
	if (wall_side == 'S')
		return (data->so_texture);
	else if (wall_side == 'N')
		return (data->no_texture);
	else if (wall_side == 'E')
		return (data->ea_texture);
	return (data->we_texture);
}

unsigned int	get_tex_pixel_color(int y2, t_info *info, t_point p)
{
	t_texture		*tex;
	char			*pixels;
	int				offset;
	unsigned int	color;

	tex = get_side_tex(info->wall_side, info->data);
	pixels = mlx_get_data_addr(tex->tex, &tex->tex->bits_per_pixel,
			&tex->tex->line_length, &tex->tex->endian);
	if (info->wall_side == 'N' || info->wall_side == 'S')
		p.x = (int)fmod(p.x, TILE_SIZE);
	else
		p.x = (int)fmod(p.y, TILE_SIZE);
	p.y = (y2 * TILE_SIZE) / 100;
	offset = (p.y * TILE_SIZE + p.x) * (tex->tex->bits_per_pixel / 8);
	color = (((unsigned char)pixels[offset + 2]) << 16)
		| (((unsigned char)pixels[offset + 1]) << 8)
		| ((unsigned char)pixels[offset]);
	return (color);
}
