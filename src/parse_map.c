/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/19 15:24:42 by arabelo-         ###   ########.fr       */
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
	handle_close(fd, NULL);
	return (lines);
}

char	**save_matrix(int fd, t_matrix *matrix_infos)
{
	char	**matrix;
	size_t	i;

	i = 0;
	matrix = (char **)malloc(sizeof(char *) * (matrix_infos->lines_amount + 1));
	if (!matrix)
		return (NULL);
	while (i < matrix_infos->lines_amount)
	{
		matrix[i] = get_next_line(fd);
		if (!matrix[i])
		{
			free_matrix(matrix);
			return (NULL);
		}
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

char	**get_matrix(char *file_name, t_matrix *matrix_infos)
{
	int		fd;
	char	**matrix;

	fd = handle_open(file_name);
	matrix_infos->lines_amount = count_file_lines(fd);
	fd = handle_open(file_name);
	matrix = save_matrix(fd, matrix_infos);
	if (!matrix)
	{
		ft_putendl_fd("Error: Memory allocation failed! Exiting...", 2);
		exit(EXIT_FAILURE);
	}
	handle_close(fd, matrix);
	return (matrix);
}
