/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:31:56 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/23 13:32:18 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	free_arr(game->map);
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
