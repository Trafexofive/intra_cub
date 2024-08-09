/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:30:04 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/09 21:20:10 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/raycast.h"
#include "../inc/struct.h"
#include "../inc/utils.h"
#include "../inc/defines.h"

#include <stdio.h>
#include <math.h>

//t_texture	*get_side_tex(char wall_side, t_data *data)
//{
//	if (wall_side == 'S')
//		return (data->so_texture);
//	else if (wall_side == 'N')
//		return (data->no_texture);
//	else if (wall_side == 'E')
//		return (data->ea_texture);
//	else if (wall_side == 'W')
//		return (data->we_texture);
//	return (NULL);
//}

//unsigned int	get_tex_pixel_color(t_point *point, t_info *info)
//{
//	t_img		*img_tex;
//	t_texture	*tex;

//	tex = get_side_tex(info->wall_side, info->data);
//	img_tex = tex->tex;

	

//	return 0;
//}
