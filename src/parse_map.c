/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/08 19:31:19 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function takes an array of strings
// and converts the values of each element
// into integers and put inside a node.
int	convert_line_into_coordinates(char **array, int y)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (array[i])
		if (!build_node(array[i++], x++, y))
			return (0);
	map()->coor->max_x = x;
	return (1);
}

// This function calculates the scale factor
// based on the window's and file's measurements
void	get_scaling_factor(void)
{
	map()->sf_x = map()->win->win_w / map()->coor->max_x;
	map()->sf_y = map()->win->win_h / map()->coor->max_y;
}

int	range(int max_z, int min_z)
{
	if (max_z - min_z == 0)
		return (1);
	if (max_z - min_z > 5 && max_z - min_z <= 50)
		return (5);
	return (25);
}

// This function calls the scale factor function
// to recalculate the new pixel distribuition
void	expand_map(void)
{
	t_node	*current;
	t_node	*save;

	get_scaling_factor();
	current = map()->head;
	save = current;
	while (current)
	{
		current->x *= map()->sf_x / 2;
		current->y *= map()->sf_y / 2;
		current->z *= 50 / range(map()->coor->max_z, map()->coor->min_z);
		current->origin_x = current->x;
		current->origin_y = current->y;
		current->origin_z = current->z;
		if (!current->east)
		{
			save = save->south;
			current = save;
		}
		else
			current = current->east;
	}
}

// Main function to build the data structure
void	get_matrix(char *file_name)
{
	int		fd;

	fd = handle_open(file_name);
	generate_lines(fd);
	handle_close(fd);
	set_z_max_min();
	expand_map();
	apply_rotation(map()->coor->angle_x,
		map()->coor->angle_y, map()->coor->angle_z);
	center_map();
}
