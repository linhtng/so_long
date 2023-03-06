/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:11:05 by thuynguy          #+#    #+#             */
/*   Updated: 2023/03/05 14:49:24 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "./ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# ifndef SIZE
#  define SIZE 32
#  ifndef MAX_HGT
#   define MAX_HGT 40
#   ifndef MAX_WD
#    define MAX_WD 80
#   endif
#  endif
# endif

typedef struct s_validpath
{
	int		lines;
	int		columns;
	char	**map;
	char	**visited;
	int		collects;
	int		new_start_i;
	int		new_start_j;
}	t_validpath;

enum	e_key
{
	UP = 13,
	DOWN = 1,
	LEFT = 0,
	RIGHT = 2,
	ESC = 53
};

typedef struct s_vector
{
	int	y;
	int	x;
}	t_vector;

typedef struct s_components
{
	int			lines;
	int			columns;
	int			c_num;
	t_vector	player_pos;
	t_vector	exit_pos;
}	t_components;

typedef struct s_image
{
	void		*ref;
	t_vector	size;
}	t_image;

typedef struct s_player
{
	t_image		sprite;
	t_vector	pos;
	int			gone;
}	t_player;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	t_player		player;
	t_image			collect;
	t_image			wall;
	t_image			exit;
	t_image			exit_open;
	char			**map;
	int				size_y;
	int				size_x;
	int				moves;
	int				end_game;
	int				passed_exit;
	t_components	comps;
}	t_game;

/* so_long_valid_path_utils */
char	**empty_map(char **map, t_validpath *path, int lines, int columns);
char	**ft_arrdup(char **map, int lines, t_validpath *check_path);
int		cell_inbound(int i, int j, int lines, int columns);
void	invalid_path_exit(char **map, t_validpath *check_path, char *message);
void	reset_visited(t_validpath *check_path);

/* so_long_valid_path */
void	valid_path(char **map, int lines, int columns, t_components *g_comps);

/* so_long_utils */
void	correct_extension(const char *argv);
void	clean_exit(char *message);
void	free_arr(char **arr);
void	malloc_error(char *message, char **mem1, char **mem2);
int		count_occurences(char *str, char c);

/* so_long_valid_map */
void	rectangular_check(char **map, int lines, int columns, int arr_len);
void	valid_characters_check(char *line, char *valid_chars, char *map_string);
void	cep0_check(char *map_str, t_components *game_comps);
void	valid_walls(char **map, int lines, int columns);

/* so_long_game_keys */
int		move_up(t_game *game);
int		move_down(t_game *game);
int		move_left(t_game *game);
int		move_right(t_game *game);
void	update_window(t_game *game);

/* so_long_game_utils */
int		close_window(t_game *game);
t_image	new_sprite(void *mlx, char *img_addr);
void	sprite_init(t_game *game);

/* so_long_game_utils */
int		key_pressed(int key, t_game *game);
void	sprite_init(t_game *game);
void	assign_img(t_game *game, char c, int x, int y);
int		load_image(t_game *game, char **map_arr);
void	game_init(char **map_arr, t_components game_comps);

#endif
