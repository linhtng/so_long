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

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	free_arr(game->map_arr);
	exit(0);
}

t_image	new_sprite(void *mlx, char *img_addr)
{
	t_image	sprite;

	sprite.size.col = 0;
	sprite.size.row = 0;
	sprite.reference = mlx_xpm_file_to_image(mlx, img_addr, &sprite.size.col, &sprite.size.row);
	return (sprite);
}

void	sprite_init(t_game *game)
{
	game->wall = new_sprite(game->mlx, "./sprites/walls.xpm");
	game->collect = new_sprite(game->mlx, "./sprites/chest0.xpm");
	game->player = new_sprite(game->mlx, "./sprites/player.xpm");
	game->exit = new_sprite(game->mlx, "./sprites/door0.xpm");
}

void	assign_img(t_game *game, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->window, game->wall.reference, x, y);
	if (c == 'C')
		mlx_put_image_to_window(game->mlx, game->window, game->collect.reference, x, y);
	if (c == 'E')
		mlx_put_image_to_window(game->mlx, game->window, game->exit.reference, x, y);
	if (c == 'P')
		mlx_put_image_to_window(game->mlx, game->window, game->player.reference, x, y);
}

void	load_image(t_game game, char **map_arr)
{
	int	row;;
	int	col;

	row = 0;
	while (row < game.game_comps.lines)
	{
		col = 0;
		while (map_arr[row][col] != '\0')
		{
			assign_img(&game, map_arr[row][col], col * SIZE, row * SIZE);
			col++;
		}
		row++;
	}
}

void	game_init(char **map_arr, t_components game_comps)
{
	t_game	game;

	game.mlx = mlx_init();
	game.window_height = game_comps.lines * SIZE;
	game.window_width = game_comps.columns * SIZE;
	game.window = mlx_new_window(game.mlx, game.window_width, game.window_height, "so_long");
	game.map_arr = map_arr;
	game.game_comps = game_comps;
	sprite_init(&game);
	load_image(game, map_arr);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
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
