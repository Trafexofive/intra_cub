/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:36:42 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 16:42:09 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	check_chars(char a, char b, char c, char d)
{
	if (ft_strchr("NSEW10", a) == NULL
		|| ft_strchr("NSEW10", b) == NULL
		|| ft_strchr("NSEW10", c) == NULL
		|| ft_strchr("NSEW10", d) == NULL)
	{
		write_fd("Error\nerror in spaces\n", 2);
	}
}

void	check_chars_g(char a, char b, char c, char d)
{
	if (ft_strchr(" 1", a) == NULL
		|| ft_strchr(" 1", b) == NULL
		|| ft_strchr(" 1", c) == NULL
		|| ft_strchr(" 1", d) == NULL)
	{
		write_fd("Error\nerror in spaces\n", 2);
	}
}

int	biggest_line(char **map)
{
	int	i;
	int	biggest;

	biggest = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > biggest)
			biggest = ft_strlen(map[i]);
		i++;
	}
	return (biggest);
}

char	*append_spaces(char *line, int size)
{
	int		line_len;
	char	*res;
	int		i;

	line_len = ft_strlen(line);
	if (size <= line_len)
		return (line);
	res = gb_malloc(sizeof(char) * (size + 1), 0);
	i = 0;
	while (i < line_len)
	{
		res[i] = line[i];
		i++;
	}
	i = line_len;
	while (i < size)
	{
		res[i] = ' ';
		i++;
	}
	res[size] = '\0';
	return (res);
}

char	**alter_map(char **map)
{
	int		biggest;
	char	**res;
	int		i;

	biggest = biggest_line(map);
	res = gb_malloc(sizeof(char *) * size_double(map) + 1, 0);
	i = 0;
	while (i < size_double(map))
	{
		res[i] = append_spaces(map[i], biggest);
		i++;
	}
	res[i] = NULL;
	return (res);
}
