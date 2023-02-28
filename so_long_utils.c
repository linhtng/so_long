/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:36:42 by thuynguy          #+#    #+#             */
/*   Updated: 2023/02/11 19:37:27 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	exit(0);
}

void	malloc_error(char *message, char **mem1, char **mem2)
{
	if (mem1)
		free_arr(mem1);
	if (mem2)
		free_arr(mem2);
	clean_exit(message);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_occurences(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	correct_extension(const char *argv)
{
	size_t		len;
	const char	*extension;

	len = ft_strlen(argv);
	extension = ft_strnstr(argv, ".ber", len);
	if (!extension || ft_strlen(extension) != 4)
		clean_exit("Map must have .ber extension\n");
}
