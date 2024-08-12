/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:08:35 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 14:42:38 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "struct.h"
# include "utils.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

void	player_move_d(t_player *a);
void	player_move_a(t_player *a);
void	player_move_s(t_player *a);
void	player_move_w(t_player *a);
void	renderer(t_info *info);
t_map	load_map_data(t_map *map);
void	clear_window(t_mlx *mlx);
void	raycaster(t_info *a);
void	test_cast(t_info *info);

#endif
