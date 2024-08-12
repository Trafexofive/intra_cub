/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:04:46 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 14:42:29 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "struct.h"
# include <mlx.h>

void			clear_window(t_mlx *mlx);
void			draw_line(t_mlx *mlx, int len, t_point starting_position,
					bool mode);
void			draw_slant(t_info *info, t_point position, t_point target);
void			draw_tile(t_mlx *mlx, int len, t_point starting_position);
bool			put_pixel(t_img *img, t_point pixel, int color);
void			render_player(t_info *info);
int				vector_len(t_point vector);
t_point			subtract_vector(t_point start, t_point end);
t_point			add_vector(t_point start, t_point end);

t_texture		*get_side_tex(char wall_side, t_data *data);
unsigned int	get_tex_pixel_color(int y2, t_info *info, t_point p);

#endif
