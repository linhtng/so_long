/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_valid_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:20:59 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/23 13:21:49 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	rectangular_check(char **map, int lines, int columns, int arr_len)
{
	int	map_area;

	map_area = columns * lines;
	if (map_area != arr_len)
	{
		free_arr(map);
		clean_exit("Map must be rectangular\n");
		exit(0);
	}
}

void	valid_characters_check(char *line, char *valid_chars, char *map_string)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(valid_chars, line[i]))
		{
			free(line);
			if (map_string)
				free(map_string);
			clean_exit("Map has invalid character.\n");
		}
		i++;
	}
}

void	cep0_check(char *map_str, t_components *game_comps)
{
	int	exit_num;
	int	collect;
	int	start_pos;
	int	free_space;

	exit_num = count_occurences(map_str, 'E');
	collect = count_occurences(map_str, 'C');
	game_comps->collectibles = collect;
	start_pos = count_occurences(map_str, 'P');
	free_space = count_occurences(map_str, '0');
	if (!(exit_num == 1 && collect >= 1 && start_pos == 1 && free_space >= 1))
	{
		free(map_str);
		if (!free_space)
			clean_exit("Map must have free space component.\n");
		clean_exit("Map must contain 1 E, at least 1 C, and 1 P to be valid.\n");
	}
}

int	wall_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

/* valid_walled:
*	Example:
*	A-------B
*	|		|
*	|		|
*	D-------C
*/

void	valid_walls(char **map, int lines, int columns)
{
	int	wall_ab;
	int	wall_dc;
	int	wall_ad;
	int	wall_bc;
	int	i;

	wall_ab = wall_only(map[0]);
	wall_dc = wall_only(map[lines - 1]);
	wall_ad = 1;
	wall_bc = 1;
	i = 0;
	while (i < lines && wall_ab && wall_dc && wall_ad && wall_bc)
	{
		if (map[i][0] != '1')
			wall_ad = 0;
		if (map[i][columns - 1] != '1')
			wall_bc = 0;
		i++;
	}
	if (!(wall_ab && wall_dc && wall_ad && wall_bc))
	{
		free_arr(map);
		clean_exit("The map must be closed/surrounded by walls.\n");
	}
}
