/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:16:45 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/18 15:48:12 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function is the first part of the generate_lines
void	generate_line_phase_1(char **line, char ***array)
{
	if (!(*array))
	{
		free(*line);
		malloc_error();
	}
	free(*line);
}

// This function uses the result of the get_next_line
// splitted to generate nodes
void	generate_line_phase_2(int fd, char **line, char ***array, int *y)
{
	if (**array[0] != '\n' && !convert_line_into_coordinates((*array), (*y)++))
	{
		free_split(*array);
		malloc_error();
	}
	free_split(*array);
	*line = get_next_line(fd);
	*array = ft_split(*line, ' ');
}

// This function generate lines using get_next_line
void	generate_lines(int fd)
{
	char	*line;
	char	**array;
	int		y;

	line = get_next_line(fd);
	if (!line)
		malloc_error();
	array = ft_split(line, ' ');
	y = 0;
	while (line)
	{
		generate_line_phase_1(&line, &array);
		generate_line_phase_2(fd, &line, &array, &y);
	}
	map()->coor->max_y = y;
	free_split(array);
}
