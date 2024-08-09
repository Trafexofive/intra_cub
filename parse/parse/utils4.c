/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 04:30:36 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/03 17:35:37 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*res;
	int		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	res = (char *)gb_malloc(len * sizeof(char) + 1, 0);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

int	count_words(char *s, char *delimiters)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s && s[i])
	{
		if (!ft_strchr(delimiters, s[i]))
		{
			res++;
			while (*s && !ft_strchr(delimiters, *s))
				s++;
		}
		else
			s++;
	}
	return (res);
}

int	word_size(char *s, char *delimiters, int i)
{
	int	res;

	res = 0;
	while (s[i] && !ft_strchr(delimiters, s[i]))
	{
		res++;
		i++;
	}
	return (res);
}

int	fill_string(char *s, char *delimiters, char **res, int number_words)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	while (j < number_words)
	{
		while (ft_strchr(delimiters, s[i]))
			i++;
		size = word_size(s, delimiters, i);
		res[j] = ft_substr(s, i, size);
		if (res[j] == NULL)
		{
			return (1);
		}
		j++;
		i += size;
	}
	res[j] = NULL;
	return (0);
}

char	**ft_split(char *s, char *delimiters)
{
	int		number_words;
	char	**res;

	number_words = count_words(s, delimiters);
	res = (char **)gb_malloc(sizeof(char *) * (number_words + 1), 0);
	if (!res || fill_string(s, delimiters, res, number_words))
		return (NULL);
	return (res);
}
