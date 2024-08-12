/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 08:07:22 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 12:52:53 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.h"
#include <math.h>

t_player	*player_init(void)
{
	t_player	*player;

	player = gb_malloc(sizeof(t_player), 0);
	player->spawn.x = 0;
	player->spawn.y = 0;
	player->position.x = 0;
	player->position.y = 0;
	player->spawned = false;
	player->fov = M_PI / 2.5;
	player->vector.len = -1;
	return (player);
}

int	is_wall(t_info *info, int x, int y)
{
	return (info->map[y][x] == '1');
}
