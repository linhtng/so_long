/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:33:24 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/28 17:18:17 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_up(t_game *game)
{
	int	row;
	int	col;

	row = game->player.pos.y - 1;
	col = game->player.pos.x;
	if (game->map[row][col] == '1' || game->map[row][col] == '\0')
		return (0);
	else
	{
		if (game->map[row][col] == 'C')
			game->comps.c_num--;
		else if (game->map[row][col] == 'E')
			game->passed_exit = 1;
		game->map[row][col] = 'P';
		game->map[row + 1][col] = '0';
		game->player.pos.y = row;
		return (1);
	}
}

int	move_down(t_game *game)
{
	int	row;
	int	col;

	row = game->player.pos.y + 1;
	col = game->player.pos.x;
	if (game->map[row][col] == '1' || game->map[row][col] == '\0')
		return (0);
	else
	{
		if (game->map[row][col] == 'C')
			game->comps.c_num--;
		else if (game->map[row][col] == 'E')
			game->passed_exit = 1;
		game->map[row][col] = 'P';
		game->map[row - 1][col] = '0';
		game->player.pos.y = row;
		return (1);
	}
}

int	move_left(t_game *game)
{
	int	row;
	int	col;

	row = game->player.pos.y;
	col = game->player.pos.x - 1;
	if (game->map[row][col] == '1' || game->map[row][col] == '\0')
		return (0);
	else
	{
		if (game->map[row][col] == 'C')
			game->comps.c_num--;
		else if (game->map[row][col] == 'E')
			game->passed_exit = 1;
		game->map[row][col] = 'P';
		game->map[row][col + 1] = '0';
		game->player.pos.x = col;
		return (1);
	}
}

int	move_right(t_game *game)
{
	int	row;
	int	col;

	row = game->player.pos.y;
	col = game->player.pos.x + 1;
	if (game->map[row][col] == '1' || game->map[row][col] == '\0')
		return (0);
	else
	{
		if (game->map[row][col] == 'C')
			game->comps.c_num--;
		else if (game->map[row][col] == 'E')
			game->passed_exit = 1;
		game->map[row][col] = 'P';
		game->map[row][col - 1] = '0';
		game->player.pos.x = col;
		return (1);
	}
}

void	update_window(t_game *game)
{
	if (game->player.pos.x == game->comps.exit_pos.x
		&& game->player.pos.y == game->comps.exit_pos.y && !game->comps.c_num)
	{	
		game->map[game->player.pos.y][game->player.pos.x] = '0';
		game->end_game = 1;
		game->player.gone = 1;
	}
	if (game->passed_exit && (game->player.pos.x != game->comps.exit_pos.x
			|| game->player.pos.y != game->comps.exit_pos.y))
		game->map[game->comps.exit_pos.y][game->comps.exit_pos.x] = 'E';
	mlx_clear_window(game->mlx, game->window);
	load_image(game, game->map);
	if (game->end_game)
	{
		game->map[game->player.pos.y][game->player.pos.x] = '0';
		mlx_clear_window(game->mlx, game->window);
		load_image(game, game->map);
		ft_printf("All collectibles were picked. So long, see you next time!\n");
	}
}
