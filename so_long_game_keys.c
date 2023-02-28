/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:33:24 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/23 13:33:57 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_up(t_game *game)
{
	int	row;
	int	col;

	row = game->player.position.row - 1;
	col = game->player.position.col;
	if (game->map[row][col] == '1' || game->map[row][col] == '\0')
		return (0);
	else
	{
		if (game->map[row][col] == 'C')
			game->game_comps.collectibles--;
		else if (game->map[row][col] == 'E')
			game->passed_exit = 1;
		game->map[row][col] = 'P';
		game->map[row + 1][col] = '0';
		game->player.position.row = row;
		return (1);
	}
}

int	move_down(t_game *game)
{
	int	row;
	int	col;

	row = game->player.position.row + 1;
	col = game->player.position.col;
	if (game->map[row][col] == '1' || game->map[row][col] == '\0')
		return (0);
	else
	{
		if (game->map[row][col] == 'C')
			game->game_comps.collectibles--;
		else if (game->map[row][col] == 'E')
			game->passed_exit = 1;
		game->map[row][col] = 'P';
		game->map[row - 1][col] = '0';
		game->player.position.row = row;
		return (1);
	}
}

int	move_left(t_game *game)
{
	int	row;
	int	col;

	row = game->player.position.row;
	col = game->player.position.col - 1;
	if (game->map[row][col] == '1' || game->map[row][col] == '\0')
		return (0);
	else
	{
		if (game->map[row][col] == 'C')
			game->game_comps.collectibles--;
		else if (game->map[row][col] == 'E')
			game->passed_exit = 1;
		game->map[row][col] = 'P';
		game->map[row][col + 1] = '0';
		game->player.position.col = col;
		return (1);
	}
}

int	move_right(t_game *game)
{
	int	row;
	int	col;

	row = game->player.position.row;
	col = game->player.position.col + 1;
	if (game->map[row][col] == '1' || game->map[row][col] == '\0')
		return (0);
	else
	{
		if (game->map[row][col] == 'C')
			game->game_comps.collectibles--;
		else if (game->map[row][col] == 'E')
			game->passed_exit = 1;
		game->map[row][col] = 'P';
		game->map[row][col - 1] = '0';
		game->player.position.col = col;
		return (1);
	}
}

void	update_window(t_game *game)
{
	if (game->player.position.col == game->game_comps.exit_pos.col 
		&& game->player.position.row == game->game_comps.exit_pos.row && !game->game_comps.collectibles)
	{	
		game->map[game->player.position.row][game->player.position.col] = '0';
		game->end_game = 1;
		game->player.gone = 1;
	}
	if (game->passed_exit && (game->player.position.col != game->game_comps.exit_pos.col 
		|| game->player.position.row != game->game_comps.exit_pos.row))
		game->map[game->game_comps.exit_pos.row][game->game_comps.exit_pos.col] = 'E';
	mlx_clear_window(game->mlx, game->window);
	load_image(game, game->map);
	if (game->end_game)
	{
		game->map[game->game_comps.player_pos.row][game->game_comps.player_pos.col] = '0';
		mlx_clear_window(game->mlx, game->window);
		load_image(game, game->map);
		ft_printf("All collectibles were picked. So long, see you next time!\n");
	}
}
