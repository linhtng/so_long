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

int	cell_inbound(int i, int j, int lines, int columns)
{
	return (i >= 0 && i < lines && j >= 0 && j < columns);
}

char	**empty_map(char **map, int lines, int columns)
{
	char	**empty_map;
	int		i;

	empty_map = (char **) malloc(sizeof(char *) * (lines + 1));
	if (!empty_map)
	{
		free_arr(map);
		clean_exit("Empty map array allocation failed.\n");
	}
	i = 0;
	while (i < lines)
	{
		empty_map[i] = (char *) malloc(sizeof(char) * (columns + 1));
		if (!empty_map[i])
		{
			free_arr(map);
			free_arr(empty_map);
			clean_exit("Empty map array allocation failed.\n");
		}
		ft_memset(empty_map[i], '0', columns);
		empty_map[i][columns] = '\0';
		i++;
	}
	empty_map[lines] = NULL;
	return (empty_map);
}

int	is_path(t_map *path, int i, int j, char des)
{
	if (cell_inbound(i, j, path->lines, path->columns) && path->map[i][j] != '1'
	&& path->visited[i][j] == '0')
	{
		path->visited[i][j] = 1;
		if (path->map[i][j] == des)
			return (1);
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

void	reset_visited(t_map *check_path)
{
	int		i;

	i = 0;
	while (i < check_path->lines)
	{
		ft_memset(check_path->visited[i], '0', check_path->columns);
		check_path->visited[i][check_path->columns] = '\0';
		i++;
	}
}

int	path_exist(t_map *path, char start, char des)
{
	int	i;
	int	j;

	i = 1;
	while (i < path->lines)
	{
		j = 0;
		while (j < path->columns)
		{
			if (path->map[i][j] == start && path->visited[i][j] == '0')
			{
				if (is_path(path, i, j, des))
				{
					reset_visited(path);
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	valid_path(char **map, int lines, int columns, int collectibles)
{
	char	**visited_cells;
	t_map	*check_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	visited_cells = empty_map(map, lines, columns);
	check_path = (t_map *) malloc(sizeof(t_map));
	if (!check_path)
	{
		free_arr(map);
		free_arr(visited_cells);
		clean_exit("Check valid path map struct allocation failed.\n");
	}
	check_path->lines = lines;
	check_path->columns = columns;
	check_path->map = map;
	check_path->visited = visited_cells;
	check_path->collects = collectibles;
	if (path_exist(check_path, 'P', 'C'))
		ft_printf("Path from P to C exit.\n");
	if (collectibles == 1)
	{
		if (path_exist(check_path, 'C', 'E'))
			ft_printf("Path from C to E exit.\n");
	}
	/* else if (collectibles > 1)
	{
		//currently stuck here 'cause we need the reset the visited matrix after each time finding a path,
		before finding the path again, otherwise that cell 'C' still marked as visited from previous call and won't
		be checked as starting point in path_exist(check_path, 'C', 'E'). But once reset, we don't know which
		C is used as start in that function call?
		if (path_exist(check_path, 'C', 'C'))
		{
			if (path_exist(check_path, 'C', 'E'))
				ft_printf("Path from C to E exit.\n");
		}
	} */
	return (0);
}
