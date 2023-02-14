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

typedef struct s_map
{
	int     lines;
	int     columns;
    char    **map;
    char    **visited;
    int     collects;
/*     char    start;
    char    collect;
    char    exit; */
}	t_map;

void	clean_exit(char *message);
void	free_arr(char **arr);
int	valid_path(char **map, int lines, int columns, int collectibles);
void	print_arr(char **arr);
#endif