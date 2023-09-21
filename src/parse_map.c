/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/20 19:21:04 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	count_file_lines(int fd)
{
	size_t	lines;
	char	*line;

	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		lines++;
	}
	handle_close(fd);
	return (lines);
}

void	save_matrix(int fd)
{
	size_t	i;

	i = 0;
	map()->map = (char **)malloc(sizeof(char *) * (map()->lines_amount + 1));
	if (!map()->map)
		exit(EXIT_FAILURE);
	while (i < map()->lines_amount)
	{
		map()->map[i] = get_next_line(fd);
		if (!map()->map[i])
		{
			free_matrix(map()->map);
			malloc_error();
		}
		i++;
	}
	map()->map[i] = NULL;
}

void	get_matrix(char *file_name)
{
	int		fd;

	fd = handle_open(file_name);
	map()->lines_amount = count_file_lines(fd);
	fd = handle_open(file_name);
	save_matrix(fd);
	if (!map()->map)
	{
		ft_putendl_fd("Error: Memory allocation failed! Exiting...", 2);
		exit(EXIT_FAILURE);
	}
	handle_close(fd);
	map()->columns_amount = ft_strlen(map()->map[0]);
	ft_printf("columns_amount: %u\n", map()->columns_amount);
}
