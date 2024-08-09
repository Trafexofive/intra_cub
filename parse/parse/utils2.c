/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:40:51 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/04 13:39:35 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_strchr(char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

int	ft_atoi(char *str)
{
	int					i;
	long long			res;
	int					sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -sign;
		i++;
	}
	while (str[i] && str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 14)
		return (INT_MAX);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = (str[i++] - '0') + (res * 10);
	res *= sign;
	return ((int)res);
}

void	check_texture(char *text, char *msg)
{
	int	fd;

	check_extention(text, ".xpm");
	fd = open(text, O_RDONLY);
	if (fd == -1)
		write_fd(msg, 2);
	else
		close(fd);
}

void	check_textures(t_data **map_data_adr)
{
	t_data	*map_data;

	map_data = *map_data_adr;
	check_texture(map_data->no_tex, "Error\nerror openning north texture\n");
	check_texture(map_data->so_tex, "Error\nerror openning south texture\n");
	check_texture(map_data->ea_tex, "Error\nerror openning east texture\n");
	check_texture(map_data->we_tex, "Error\nerror openning west texture\n");
}

int	check(char *val)
{
	if (!val)
		return (1);
	write_fd("Error\nduplicated resources\n", 2);
	return (0);
}
