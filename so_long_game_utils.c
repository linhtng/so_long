/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:31:56 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/28 20:56:09 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	free_arr(game->map);
	exit(EXIT_SUCCESS);
}

t_image	new_sprite(void *mlx, char *img_addr)
{
	t_image	img;

	img.size.x = 0;
	img.size.y = 0;
	img.ref = mlx_xpm_file_to_image(mlx, img_addr, &img.size.x, &img.size.y);
	return (img);
}

void	assign_img(t_game *g, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(g->mlx, g->window, g->wall.ref, x, y);
	if (c == 'C')
		mlx_put_image_to_window(g->mlx, g->window, g->collect.ref, x, y);
	if (c == 'P')
		mlx_put_image_to_window(g->mlx, g->window, g->player.sprite.ref, x, y);
	if (c == 'E' && g->comps.c_num)
		mlx_put_image_to_window(g->mlx, g->window, g->exit.ref, x, y);
	else if (c == 'E' && !g->comps.c_num)
		mlx_put_image_to_window(g->mlx, g->window, g->exit_open.ref, x, y);
}

void	sprite_init(t_game *game)
{
	game->wall = new_sprite(game->mlx, "./sprites/walltest.xpm");
	game->collect = new_sprite(game->mlx, "./sprites/key.xpm");
	game->player.sprite = new_sprite(game->mlx, "./sprites/player0.xpm");
	game->exit = new_sprite(game->mlx, "./sprites/door02.xpm");
	game->exit_open = new_sprite(game->mlx, "./sprites/door02.o.xpm");
}
