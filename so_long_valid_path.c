/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_valid_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:36:55 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/14 13:59:15 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_path(t_validpath *path, int i, int j, char des)
{
	if (cell_inbound(i, j, path->lines, path->columns) && path->map[i][j] != '1'
	&& path->visited[i][j] == '0')
	{
		path->visited[i][j] = 1;
		if (path->map[i][j] == des)
		{
			path->new_start_i = i;
			path->new_start_j = j;
			return (1);
		}
		if (is_path(path, i - 1, j, des))
			return (1);
		if (is_path(path, i + 1, j, des))
			return (1);
		if (is_path(path, i, j - 1, des))
			return (1);
		if (is_path(path, i, j + 1, des))
			return (1);
	}
	return (0);
}

int	path_to_exit(t_validpath *path, char start, char des, t_components *g_comps)
{
	int	i;
	int	j;

	i = 1;
	reset_visited(path);
	while (i < path->lines)
	{
		j = 0;
		while (j < path->columns)
		{
			if (path->map[i][j] == start)
			{
				if (is_path(path, i, j, des))
				{
					g_comps->exit_pos.y = path->new_start_i;
					g_comps->exit_pos.x = path->new_start_j;
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	path_for_multi_c(t_validpath *path, int i, int j, int collectibles)
{
	while (collectibles > 0)
	{
		collectibles--;
		if (is_path(path, i, j, 'C'))
		{
			i = path->new_start_i;
			j = path->new_start_j;
			path->map[i][j] = '2';
			path->collects--;
			reset_visited(path);
		}
	}
	if (path->collects == 0)
	{
		path->map[i][j] = 'C';
		return (1);
	}
	return (0);
}

int	path_to_all_c(t_validpath *path, char start, char des, t_components *gcomps)
{
	int	i;
	int	j;

	i = 1;
	while (i < path->lines)
	{
		j = 0;
		while (j < path->columns)
		{
			if (path->map[i][j] == start)
			{
				gcomps->player_pos.y = i;
				gcomps->player_pos.x = j;
				if (gcomps->c_num == 1)
					return (is_path(path, i, j, des));
				else
					return (path_for_multi_c(path, i, j, gcomps->c_num));
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	valid_path(char **map, int lines, int columns, t_components *game_comps)
{
	t_validpath	*check_path;

	check_path = (t_validpath *) malloc(sizeof(t_validpath));
	if (!check_path)
	{
		free_arr(map);
		clean_exit("Check valid path map struct allocation failed.\n");
	}
	check_path->lines = lines;
	check_path->columns = columns;
	check_path->map = ft_arrdup(map, lines, check_path);
	check_path->visited = empty_map(map, check_path, lines, columns);
	check_path->collects = game_comps->c_num;
	if (path_to_all_c(check_path, 'P', 'C', game_comps))
	{
		if (!path_to_exit(check_path, 'C', 'E', game_comps))
			invalid_path_exit(map, check_path, "No valid path to E.\n");
	}
	else
		invalid_path_exit(map, check_path, "No valid path to collect all C.\n");
	free_arr(check_path->map);
	free_arr(check_path->visited);
	free(check_path);
}
