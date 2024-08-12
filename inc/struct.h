/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:09:33 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 16:39:45 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub.h"
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum s_comp
{
	north = 0,
	west = 1,
	east = 2,
	south = 3,
}				t_comp;

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_vector
{
	t_point		start;
	t_point		end;
	double		len;
}				t_vector;

typedef struct s_game_vars
{
	t_point		draw_cursor;
	t_point		player_position;
	double		player_fov;

}				t_game;

typedef struct s_player
{
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		angle;
	t_point		spawn;
	double		fov;
	t_comp		player_dir;
	t_point		position;
	t_vector	last_ray;
	t_vector	vector;
	bool		spawned;
}				t_player;

typedef struct s_info
{
	t_mlx		*mlx;
	char		wall_side;
	char		**map;
	t_player	*player;
	t_game		*vars;
	t_img		img;
	t_data		*data;
	double		wall_h;
	double		dis;
	int			draw_start;
	int			draw_end;
}				t_info;

#endif
