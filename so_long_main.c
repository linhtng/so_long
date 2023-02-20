/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:13:23 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/09 18:16:21 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	correct_extension(const char *argv)
{
	size_t		len;
	const char	*extension;

	len = ft_strlen(argv);
	extension = ft_strnstr(argv, ".ber", len);
	if (!extension || ft_strlen(extension) != 4)
		clean_exit("Map must have .ber extension\n");
}

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

char	*get_map_string(int fd, t_components *game_comp)
{
	char	*buf;
	char	*map_string;

	map_string = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		valid_characters_check(buf, "01CEP\n", map_string);
		map_string = ft_strjoin(map_string, buf);
		if (!map_string)
		{
			free(buf);
			clean_exit("Map string allocation failed.\n");
		}
		game_comp->lines++;
		free(buf);
		buf = get_next_line(fd);
	}
	return(map_string);
}

char	**get_map_array(char *map_str, t_components *game_comps)
{
	char	**map;

	map = NULL;
	cep0_check(map_str, game_comps);
	map = ft_split(map_str, '\n');
	if (!map)
	{
		free(map_str);
		clean_exit("Map array allocation failed.\n");
	}
	free(map_str);
	return (map);
}

char	**get_valid_map(int fd, t_components *game_comps)
{
	char	**map;
	char	*map_string;
	int		arr_len;

	arr_len = 0;
	map = NULL;
	map_string = get_map_string(fd, game_comps);
	arr_len = ft_strlen(map_string) - count_occurences(map_string, '\n');
	if (map_string)
		map = get_map_array(map_string, game_comps);
	else
		clean_exit("Map is empty.\n");
	if (map)
	{
		game_comps->columns = ft_strlen(map[0]);
		rectangular_check(map, game_comps->lines, game_comps->columns, arr_len);
		valid_walls(map, game_comps->lines, game_comps->columns);
		valid_path(map, game_comps->lines, game_comps->columns, game_comps);
	}
	return (map);
}

void	game_comps_init(t_components *game_comps)
{
	game_comps->lines = 0;
	game_comps->columns = 0;
	game_comps->collectibles = 0;
	game_comps->player_pos.row = 0;
	game_comps->player_pos.col = 0;
	game_comps->exit_pos.row = 0;
	game_comps->exit_pos.col = 0;
}

void	print_game_comps(t_components *game_comps)
{
	ft_printf("Lines: %d\n", game_comps->lines);
	ft_printf("Columns: %d\n", game_comps->columns);
	ft_printf("Collectibles: %d\n", game_comps->collectibles);
	ft_printf("Player x: %d\n", game_comps->player_pos.row);
	ft_printf("Player y: %d\n", game_comps->player_pos.col);
	ft_printf("Exit x: %d\n", game_comps->exit_pos.row);
	ft_printf("Exit y: %d\n", game_comps->exit_pos.col);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_components	game_comps;
	char			**map;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);	
		if (fd == -1)
			clean_exit("File cannot be opened.\n");
		correct_extension(argv[1]);
		game_comps_init(&game_comps);
		map = get_valid_map(fd, &game_comps);
		print_game_comps(&game_comps);
	}
	else
		clean_exit("Number of parameters must be 1.\n");
	return (0);
}
