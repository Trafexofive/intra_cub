/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_and_collision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:48:00 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 08:15:04 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/macros.h"

void	update_player_position(t_info *info, double move_speed,
		double strafe_speed)
{
	t_player	*player;
	t_point		move;
	t_point		strafe;
	t_point		new;

	player = info->player;
	move.x = cos(player->angle) * move_speed;
	move.y = sin(player->angle) * move_speed;
	strafe.x = cos(player->angle + M_PI / 2) * strafe_speed;
	strafe.y = sin(player->angle + M_PI / 2) * strafe_speed;
	new.x = player->vector.start.x + move.x + strafe.x;
	new.y = player->vector.start.y + move.y + strafe.y;
	check_collision(info, move, strafe, new);
}

void	help_movement(int key, t_player **player_adr, double rotation_speed)
{
	t_player	*player;

	player = *player_adr;
	if (key == RIGHT_KEY)
	{
		player->angle += rotation_speed;
		if (player->angle < 0)
			player->angle += 2 * M_PI;
	}
	if (key == LEFT_KEY)
	{
		player->angle -= rotation_speed;
		if (player->angle > 2 * M_PI)
			player->angle -= 2 * M_PI;
	}
}

void	handle_player_movement(t_info *info, int key)
{
	double		move_speed;
	double		rotation_speed;
	t_player	*player;

	move_speed = 5.0;
	rotation_speed = 0.1;
	player = info->player;
	if (key == W_KEY)
		update_player_position(info, move_speed, 0);
	if (key == S_KEY)
		update_player_position(info, -move_speed, 0);
	if (key == A_KEY)
		update_player_position(info, 0, -move_speed);
	if (key == D_KEY)
		update_player_position(info, 0, move_speed);
	help_movement(key, &player, rotation_speed);
}

static int	sgn(double x)
{
	return ((x > 0) - (x < 0));
}

void	check_collision(t_info *info, t_point move, t_point strafe, t_point new)
{
	t_player	*player;

	player = info->player;
	if (!is_wall(info, (int)((new.x + COLLISION_MARGIN * sgn(move.x + strafe.x))
			/ TILE_SIZE), (int)(player->vector.start.y / TILE_SIZE))
		&& !is_wall(info, (int)((new.x + COLLISION_MARGIN * sgn(move.x
						+ strafe.x)) / TILE_SIZE), (int)((player->vector.start.y
					+ PLAYER_SIZE / 2) / TILE_SIZE)) && !is_wall(info,
			(int)((new.x + COLLISION_MARGIN * sgn(move.x + strafe.x))
				/ TILE_SIZE), (int)((player->vector.start.y - PLAYER_SIZE / 2)
				/ TILE_SIZE)))
	{
		player->vector.start.x = new.x;
	}
	if (!is_wall(info, (int)(player->vector.start.x / TILE_SIZE), (int)((new.y
			+ COLLISION_MARGIN * sgn(move.y + strafe.y)) / TILE_SIZE))
		&& !is_wall(info, (int)((player->vector.start.x + PLAYER_SIZE / 2)
				/ TILE_SIZE), (int)((new.y + COLLISION_MARGIN * sgn(move.y
						+ strafe.y)) / TILE_SIZE)) && !is_wall(info,
			(int)((player->vector.start.x - PLAYER_SIZE / 2) / TILE_SIZE),
			(int)((new.y + COLLISION_MARGIN * sgn(move.y + strafe.y))
				/ TILE_SIZE)))
	{
		player->vector.start.y = new.y;
	}
}
