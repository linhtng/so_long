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

int	count_occurences(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	cep_check(char *map_str, int *collectibles)
{
	int	exit_num;
	int	collect;
	int	start_pos;

	exit_num = count_occurences(map_str, 'E');
	collect = count_occurences(map_str, 'C');
	*collectibles = collect;
	start_pos = count_occurences(map_str, 'P');
	if (!(exit_num == 1 && collect >= 1 && start_pos == 1))
	{
		free(map_str);
		clean_exit("The map must contain 1 E, at least 1 C, and 1 P to be valid.\n");
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
	int	wall_AB;
	int	wall_DC;
	int	wall_AD;
	int	wall_BC;
	int	i;

	wall_AB = wall_only(map[0]);
	wall_DC = wall_only(map[lines - 1]);
	wall_AD = 1;
	wall_BC = 1;
	i = 0;
	while (i < lines && wall_AB && wall_DC && wall_AD && wall_BC)
	{
		if (map[i][0] != '1')
			wall_AD = 0;
		if (map[i][columns - 1] != '1')
			wall_BC = 0;
		i++;
	}
	if (!(wall_AB && wall_DC && wall_AD && wall_BC))
	{
		free_arr(map);
		clean_exit("The map must be closed/surrounded by walls.\n");
	}
}

char	**get_valid_map(char **argv, int fd)
{
	char	**map;
	char	*buf;
	char	*map_string;
	int		lines;
	int		columns;
	int		arr_len;
	int		collectibles;

	correct_extension(argv[1]);
	map = NULL;
	map_string = NULL;
	arr_len = 0;
	lines = 0;
	columns = 0;
	collectibles = 0;
	while ((buf = get_next_line(fd)) != NULL)
	{
		valid_characters_check(buf, "01CEP\n", map_string);
		map_string = ft_strjoin(map_string, buf);
		if (!map_string)
		{
			free(buf);
			clean_exit("Map string allocation failed.\n");
		}
		lines++;
		free(buf);
	}
	if (map_string)
	{
		cep_check(map_string, &collectibles);
		map = ft_split(map_string, '\n', &arr_len);
		if (!map)
		{
			free(map_string);
			clean_exit("Map array allocation failed.\n");
		}
		free(map_string);
	}
	else
		clean_exit("Map is empty.\n");
	if (map)
	{
		columns = ft_strlen(map[0]);
		rectangular_check(map, lines, columns, arr_len);
		valid_walls(map, lines, columns);
		if (!valid_path(map, lines, columns, collectibles))
		{
			free(map);
			clean_exit("Valid path check failed.");
		}
	}
	return (map);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	**map;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			clean_exit("File cannot be opened.\n");
		}
		map = get_valid_map(argv, fd);
		if (map)
			print_arr(map);
	}
	else
		clean_exit("Number of parameters must be 1.\n");
	return (0);
}
