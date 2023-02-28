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

void	sprite_init(t_game *game)
{
	game->wall = new_sprite(game->mlx, "./sprites/walltest.xpm");
	game->collect.sprite = new_sprite(game->mlx, "./sprites/key.xpm");
	game->player.sprite = new_sprite(game->mlx, "./sprites/player0.xpm");
	game->exit = new_sprite(game->mlx, "./sprites/door02.xpm");
	game->exit_open = new_sprite(game->mlx, "./sprites/door02.o.xpm");
	game->floor = new_sprite(game->mlx, "./sprites/floor.xpm");
}

void	assign_img(t_game *game, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->window, game->wall.reference, x, y);
	if (c == 'C')
		mlx_put_image_to_window(game->mlx, game->window, game->collect.sprite.reference, x, y);
	if (c == 'P')
		mlx_put_image_to_window(game->mlx, game->window, game->player.sprite.reference, x, y);
	if (c == 'E' && game->game_comps.collectibles)
		mlx_put_image_to_window(game->mlx, game->window, game->exit.reference, x, y);
	else if (c == 'E' && !game->game_comps.collectibles)
		mlx_put_image_to_window(game->mlx, game->window, game->exit_open.reference, x, y);
}

int	load_image(t_game *game, char **map_arr)
{
	int	row;;
	int	col;

	row = 0;
	while (row < game->game_comps.lines)
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

void	game_init(char **map_arr, t_components game_comps)
{
	t_game	game;

	game.mlx = mlx_init();
	game.window_height = game_comps.lines * SIZE;
	game.window_width = game_comps.columns * SIZE;
	game.window = mlx_new_window(game.mlx, game.window_width, game.window_height, "so_long");
	game.map = map_arr;
	game.game_comps = game_comps;
	game.player.position = game_comps.player_pos;
	game.player.gone = 0;
	game.moves = 0;
	game.end_game = 0;
	sprite_init(&game);
	load_image(&game, map_arr);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_hook(game.window, 2, 0, key_pressed, &game);
	mlx_loop(game.mlx);
}
