/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:01:14 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 16:40:45 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	ft_strlen(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		i++;
	return (i);
}

char	*trim_behind(char *buffer)
{
	int			last_index;
	char		*res;
	int			i;

	last_index = ft_strlen(buffer) - 1;
	if (buffer[last_index] == '\n')
		last_index--;
	while (buffer[last_index] && (buffer[last_index] == ' '
			|| buffer[last_index] == '\t'))
	{
		last_index--;
	}
	res = (char *)gb_malloc(last_index + 2, 0);
	i = 0;
	while (i <= last_index)
	{
		res[i] = buffer[i];
		i++;
	}
	res[last_index + 1] = '\0';
	return (res);
}

void	write_fd(char *data, int fd)
{
	write(fd, data, ft_strlen(data));
	exit(1);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 == '\0')
			break ;
		s1++;
		s2++;
		n--;
	}
	return (0);
}

int	size_double(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
