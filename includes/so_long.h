/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:11:05 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/09 18:11:11 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "./ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# ifndef SIZE
#  define SIZE 32
# endif

typedef struct s_validpath
{
	int     lines;
	int     columns;
    char    **map;
    char    **visited;
    int     collects;
    int     new_start_i;
    int     new_start_j;
}	t_validpath;

typedef struct s_vector
{
    int     row;
    int     col;
}	t_vector;

typedef struct s_components
{
	int         lines;
	int         columns;
    int         collectibles;
    t_vector    player_pos;
    t_vector    exit_pos;
}	t_components;

typedef struct s_image
{
	void        *reference;
    t_vector    size;
}	t_image;

typedef struct s_game
{
    void            *mlx;
    void            *window;
    t_image         collect;
    t_image         player;
    t_image         wall;
    t_image         exit;
    char            **map_arr;
    int             window_height;
    int             window_width;
    t_components    game_comps;
}	t_game;

void	clean_exit(char *message);
void	free_arr(char **arr);
void	valid_path(char **map, int lines, int columns, t_components *game_comps);
void	print_arr(char **arr);
void	malloc_error(char *message, char **mem1, char **mem2);
int	    count_occurences(char *str, char c);
int	    count_occurences_arr(char **arr, int lines, char c);

/* so_long_valid_path_utils */
char	**empty_map(char **map, t_validpath *check_path, int lines, int columns);
char	**ft_arrdup(char **map, int lines, t_validpath *check_path);
int	    cell_inbound(int i, int j, int lines, int columns);
void	invalid_path_exit(char **map, t_validpath *check_path, char *message);
void	reset_visited(t_validpath *check_path);

#endif