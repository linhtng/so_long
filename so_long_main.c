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
	game_comps->c_num = 0;
	game_comps->player_pos.y = 0;
	game_comps->player_pos.x = 0;
	game_comps->exit_pos.y = 0;
	game_comps->exit_pos.x = 0;
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
		if (map)
			game_init(map, game_comps);
	}
	else
		clean_exit("Number of parameters must be 1.\n");
	return (0);
}
