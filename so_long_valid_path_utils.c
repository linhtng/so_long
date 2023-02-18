/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_valid_path_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:55:15 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/18 18:02:42 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**empty_map(char **map, t_validpath *path, int lines, int columns)
{
	char	**empty_map;
	int		i;

	empty_map = (char **) malloc(sizeof(char *) * (lines + 1));
	if (!empty_map)
	{
		free(path);
		malloc_error("Empty map array allocation failed.\n", map, path->map);
	}
	i = 0;
	while (i < lines)
	{
		empty_map[i] = (char *) malloc(sizeof(char) * (columns + 1));
		if (!empty_map[i])
		{
			free_arr(empty_map);
			free(path);
			malloc_error("Empty map array allocation failed.\n", map, path->map);
		}
		ft_memset(empty_map[i], '0', columns);
		empty_map[i][columns] = '\0';
		i++;
	}
	empty_map[lines] = NULL;
	return (empty_map);
}

char	**ft_arrdup(char **map, int lines, t_validpath *check_path)
{
	char	**dup;
	int		i;

	dup = (char **) malloc(sizeof(char *) * (lines + 1));
	if (!dup)
	{
		free_arr(map);
		free(check_path);
		clean_exit("Duplicate map array allocation failed.\n");
	}
	i = 0;
	while (i < lines)
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
		{
			free(check_path);
			malloc_error("Duplicate map array allocation failed.\n", map, dup);
		}
		i++;
	}
	dup[lines] = NULL;
	return (dup);
}

int	cell_inbound(int i, int j, int lines, int columns)
{
	return (i >= 0 && i < lines && j >= 0 && j < columns);
}

void	invalid_path_exit(char **map, t_validpath *check_path, char *message)
{
	free_arr(map);
	free_arr(check_path->map);
	free_arr(check_path->visited);
	free(check_path);
	clean_exit(message);
}

void	reset_visited(t_validpath *check_path)
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
