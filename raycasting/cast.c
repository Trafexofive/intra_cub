/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 08:06:56 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 18:50:05 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"
#include <mlx.h>

typedef struct s_wall_info
{
	double	corrected_dist;
	double	wall_height;
	int		draw_start;
	int		draw_end;
}			t_wall_info;

void	calculate_wall_dimensions(t_wall_info *wi, t_info *info, double dist,
		double angle)
{
	wi->corrected_dist = dist * cos(angle - info->player->angle);
	wi->wall_height = (SCREEN_HEIGHT / wi->corrected_dist) * TILE_SIZE;
	wi->draw_start = (SCREEN_HEIGHT - wi->wall_height) / 2;
	wi->draw_end = (SCREEN_HEIGHT + wi->wall_height) / 2;
	if (wi->draw_end >= SCREEN_HEIGHT)
		wi->draw_end = SCREEN_HEIGHT - 1;
	info->dis = wi->corrected_dist;
	info->wall_h = wi->wall_height;
	info->draw_start = wi->draw_start;
	info->draw_end = wi->draw_end;
}

void	draw_wall_column(t_info *info, int x, t_point p, t_wall_info *wi)
{
	t_img	*image;
	t_point	point;
	int		y2;
	int		color;

	image = &info->img;
	point.x = x;
	for (int y = wi->draw_start; y <= wi->draw_end; y++)
	{
		if (y < 0 || y >= SCREEN_HEIGHT)
			continue ;
		y2 = ((y - wi->draw_start) * 100) / wi->wall_height;
		point.y = y;
		color = get_tex_pixel_color(y2, info, p);
		put_pixel(image, point, color);
	}
}

void	draw_wall_strip(t_info *info, int x, double dist, double angle,
		t_point p)
{
	t_wall_info	wi;

	calculate_wall_dimensions(&wi, info, dist, angle);
	draw_wall_column(info, x, p, &wi);
}

void	put_floor_color(t_info *info, int color)
{
	t_img	*image;
	t_point	point;

	image = &info->img;
	point.x = 0;
	point.y = SCREEN_HEIGHT / 2;
	while (point.y < SCREEN_HEIGHT)
	{
		while (point.x < SCREEN_WIDTH)
		{
			put_pixel(image, point, color);
			point.x += 1;
		}
		point.x = 0;
		point.y += 1;
	}
}

void	put_skye_color(t_info *info, int color)
{
	t_img	*image;
	t_point	point;

	image = &info->img;
	point.x = 0;
	point.y = 0;
	while (point.y < SCREEN_HEIGHT / 2)
	{
		while (point.x < SCREEN_WIDTH)
		{
			put_pixel(image, point, color);
			point.x += 1;
		}
		point.x = 0;
		point.y += 1;
	}
}

void set_player_spawn(t_info *info) {
    char **map = info->map;
    int i;
    int j;

	i = 0;
	j = 0;
    while (map[j]) {
        while (map[j][i]) {
            if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W' ||
                map[j][i] == 'E') {
                info->player->vector.start.x = i * TILE_SIZE + TILE_SIZE / 2;
                info->player->vector.start.y = j * TILE_SIZE + TILE_SIZE / 2;
                if (map[j][i] == 'E') {
                    info->player->angle = 0;
                } else if (map[j][i] == 'S') {
                    info->player->angle = M_PI / 2;
                } else if (map[j][i] == 'W') {
                    info->player->angle = M_PI;
                } else if (map[j][i] == 'N') {
                    info->player->angle = 3 * M_PI / 2;
                }
                return;
            }
            i++;
        }
        i = 0;
        j++;
    }
}

typedef struct s_ray_info
{
	t_point	dir;
	t_point	ray_step;
	t_point	ray_len;
	t_point	step;
	int		map_x;
	int		map_y;
}			t_ray_info;

void	initialize_ray_direction(t_ray_info *ri, t_point pos, double angle)
{
	ri->dir.x = cos(angle);
	ri->dir.y = sin(angle);
	ri->ray_step.x = fabs(TILE_SIZE / ri->dir.x);
	ri->ray_step.y = fabs(TILE_SIZE / ri->dir.y);
	ri->map_x = (int)(pos.x / TILE_SIZE);
	ri->map_y = (int)(pos.y / TILE_SIZE);
}

void	calculate_ray_length(t_ray_info *ri, t_point pos)
{
	if (ri->dir.x < 0)
	{
		ri->step.x = -1;
		ri->ray_len.x = (pos.x - ri->map_x * TILE_SIZE) * ri->ray_step.x
			/ TILE_SIZE;
	}
	else
	{
		ri->step.x = 1;
		ri->ray_len.x = ((ri->map_x + 1) * TILE_SIZE - pos.x) * ri->ray_step.x
			/ TILE_SIZE;
	}
	if (ri->dir.y > 0)
	{
		ri->step.y = 1;
		ri->ray_len.y = ((ri->map_y + 1) * TILE_SIZE - pos.y) * ri->ray_step.y
			/ TILE_SIZE;
	}
	else
	{
		ri->step.y = -1;
		ri->ray_len.y = (pos.y - ri->map_y * TILE_SIZE) * ri->ray_step.y
			/ TILE_SIZE;
	}
}

void	calculate_step(t_ray_info *ri, double *dist, t_info *info)
{
	if (ri->ray_len.x < ri->ray_len.y)
	{
		ri->map_x += ri->step.x;
		*dist = ri->ray_len.x;
		ri->ray_len.x += ri->ray_step.x;
		if (ri->dir.x < 0)
			info->wall_side = 'W';
		else
			info->wall_side = 'E';
	}
	else
	{
		ri->map_y += ri->step.y;
		*dist = ri->ray_len.y;
		ri->ray_len.y += ri->ray_step.y;
		if (ri->dir.y < 0)
			info->wall_side = 'N';
		else
			info->wall_side = 'S';
	}
}

int	perform_dda(t_info *info, t_ray_info *ri, double *dist)
{
	int		hit;
	char	**map;

	hit = 0;
	map = info->map;
	while (!hit && ri->map_x >= 0 && ri->map_y >= 0)
	{
		calculate_step(ri, dist, info);
		if (ri->map_x >= 0 && ri->map_y >= 0)
		{
			if (map[ri->map_y][ri->map_x] != '0'
				&& map[ri->map_y][ri->map_x] != 'N'
				&& map[ri->map_y][ri->map_x] != 'S'
				&& map[ri->map_y][ri->map_x] != 'W'
				&& map[ri->map_y][ri->map_x] != 'E')
			{
				hit = 1;
			}
		}
	}
	return (hit);
}

double	raycast(t_point pos, double angle, t_vector *vector, t_info *info)
{
	t_ray_info	ri;
	double		dist;

	dist = 0;
	initialize_ray_direction(&ri, pos, angle);
	calculate_ray_length(&ri, pos);
	perform_dda(info, &ri, &dist);
	vector->start = pos;
	vector->end.x = (int)(pos.x + ri.dir.x * dist) % TILE_SIZE;
	vector->end.y = (int)(pos.y + ri.dir.y * dist);
	return (dist);
}

void	check_reset_player_angle(t_player *player)
{
	if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
}

void	test_cast(t_info *info)
{
	t_vector	vector;
	double		dist;
	double		fov;
	int			x;
	double		ray_angle;

	if (info->player->vector.len == -1)
	{
		set_player_spawn(info);
		info->player->vector.len = -2;
	}
	clear_window(info->mlx);
	put_floor_color(info, info->data->color_f);
	put_skye_color(info, info->data->color_c);
	fov = info->player->fov;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_angle = info->player->angle - fov / 2 + (x / (double)SCREEN_WIDTH)
			* fov;
		dist = raycast(info->player->vector.start, ray_angle, &vector, info);
		draw_wall_strip(info, x, dist, ray_angle, vector.end);
		x++;
	}
	check_reset_player_angle(info->player);
}
