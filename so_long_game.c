/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:27:09 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/23 13:31:31 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_pressed(int key, t_game *game)
{
	int	moved;

	moved = 0;
	if (key == UP && !game->player.gone)
		moved = move_up(game);
	else if (key == DOWN && !game->player.gone)
		moved = move_down(game);
	else if (key == LEFT && !game->player.gone)
		moved = move_left(game);
	else if (key == RIGHT && !game->player.gone)
		moved = move_right(game);
	else if (key == ESC)
		close_window(game);
	else
		return (0);
	if (moved)
	{
		game->moves++;
		ft_printf("Number of moves: %d\n", game->moves);
	}
	update_window(game);
	return (0);
}

void	get_top_left_y(t_game *game, int *y)
{
	*y = 0;
	if (game->player.pos.y - MAX_HEIGHT / 2 > 0)
	{
		if (game->comps.lines - game->player.pos.y > MAX_HEIGHT / 2 )
			*y = game->player.pos.y - MAX_HEIGHT / 2;
		else
			*y = game->comps.lines - MAX_HEIGHT;
	}
}

int	load_image_large_map(t_game *game, char **map_arr, int row, int col)
{
	int	x;
	int	y;

	get_top_left_y(game, &y);
	while (y < game->comps.lines)
	{
		col = 0;
		x = 0;
		if (game->player.pos.x - MAX_WIDTH / 2 > 0)
		{
			if (game->comps.columns - game->player.pos.x > MAX_WIDTH / 2 )
				x = game->player.pos.x - MAX_WIDTH / 2;
			else
				x = game->comps.columns - MAX_WIDTH;
		}
		while (map_arr[y][x] != '\0')
		{
			assign_img(game, map_arr[y][x], col * SIZE, row * SIZE);
			col++;
			x++;
		}
		row++;
		y++;
	}
	return (1);	
}

int	load_image(t_game *game, char **map_arr)
{
	int	row;;
	int	col;

	row = 0;
	col = 0;
	if ((game->comps.lines > MAX_HEIGHT || game->comps.columns > MAX_WIDTH)  
		&& (game->player.pos.y > MAX_HEIGHT / 2 || game->player.pos.x > MAX_WIDTH / 2))
		return (load_image_large_map(game, map_arr, row, col));
	while (row < game->comps.lines)
	{
		col = 0;
		while (map_arr[row][col] != '\0')
		{
			assign_img(game, map_arr[row][col], col * SIZE, row * SIZE);
			col++;
		}
		row++;
	}
	return (1);
}

void	game_init(char **map_arr, t_components comps)
{
	t_game	game;

	game.mlx = mlx_init();
	if (comps.lines > MAX_HEIGHT)
		game.window_height = MAX_HEIGHT * SIZE;
	else
		game.window_height = comps.lines * SIZE;
	if (comps.columns > MAX_WIDTH)
		game.window_width = MAX_WIDTH * SIZE;
	else
		game.window_width = comps.columns * SIZE;
	game.window = mlx_new_window(game.mlx, game.window_width, game.window_height, "so_long");
	game.map = map_arr;
	game.comps = comps;
	game.player.pos = comps.player_pos;
	game.player.gone = 0;
	game.moves = 0;
	game.end_game = 0;
	sprite_init(&game);
	load_image(&game, map_arr);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_hook(game.window, 2, 0, key_pressed, &game);
	mlx_loop(game.mlx);
}
