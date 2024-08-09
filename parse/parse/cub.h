/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:01:10 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/09 19:39:18 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../get_next_line/get_next_line.h"
# include "../garbage_collector/garbage.h"

# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>


typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}				t_node;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*frame;
}				t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_texture
{
	t_img	*tex;
	int		w;
	int		h;
}				t_texture;

typedef struct s_map
{
	t_node	*map;
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	char	*color_f;
	char	*color_c;
}				t_map;

typedef struct s_data
{
	t_mlx		*ini;
	char		**map;
	char		*no_tex;
	char		*so_tex;
	char		*ea_tex;
	char		*we_tex;
	t_texture	*no_texture;
	t_texture	*so_texture;
	t_texture	*ea_texture;
	t_texture	*we_texture;
	int			color_c;
	int			color_f;
	int			player_x;
	int			player_y;
	char		player_face;
}			t_data;

t_node		*ft_lstnew(void *content);
void		ft_lstadd_back(t_node **lst, t_node *new);
t_node		*ft_lstlast(t_node *lst);
char		*ft_strchr(char *s, char c);
int			ft_strlen(char *buffer);
void		write_fd(char *data, int fd);
int			ft_strncmp(char *s1, char *s2, int n);
t_map		*parse(char *map);
void		init(t_map **all_map_adr);
void		assigner(char *buffer, t_map **all_map_adr);
int			checker(t_map **all_map_adr);
char		*trim_behind(char *buffer);
int			size_double(char **arr);
int			open_file(char *file);
int			move_to_map(char *buffer);
void		validate(t_map **all_map_adr);
void		borders(t_map **all_map_adr);
void		check_line(char *g, int mode);
int			ft_lst_size(t_node *lst);
void		elements(t_map **all_map_adr);
int			ft_getstart(char *s1, char *set);
int			ft_getend(char *s1, char *set);
char		*ft_strtrim(char *s1, char *set);
int			ft_strlcpy(char *dst, char *src, int dstsize);
t_data		*transform(t_map **all_map_adr, t_mlx **ini_adr);
char		*ft_strdup(char *s1);
int			count_words(char *s, char *delimiters);
int			word_size(char *s, char *delimiters, int i);
int			fill_string(char *s, char *delimiters, char **res, int number_words);
char		**ft_split(char *s, char *delimiters);
char		*ft_substr(char *s, int start, int len);
int			ft_atoi(char *str);
void		get_color(char *buffer, char *delim, int *fill);
void		extract_color(t_data **data_map_adr, t_map **all_map_adr);
void		assign_textures(t_data **data_map_adr, t_map **all_map_adr);
void		check_spaces(char **map);
void		check_chars(char a, char b, char c, char d);
void		check_chars_g(char a, char b, char c, char d);
int			biggest_line(char **map);
char		**alter_map(char **map);
char		*append_spaces(char *line, int size);
void		check_textures(t_data **map_data_adr);
void		check_texture(char *text, char *msg);
t_data		*parse_entry(int ac, char **av);
void		check_extention(char *buffer, char *ext);
int			check(char *val);
t_texture	*open_tex(char *path, void *mlx_ptr);
void		open_textures(t_data **all_data_adr);
void		assign_player_pos(t_data **all_data_ptr);

#endif
