/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:17:29 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/03 17:41:37 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H

# define GARBAGE_H

# include <stdlib.h>
# include <unistd.h>

# define MAX_SIZE 2048

void	*gb_malloc(size_t size, int type);

#endif
