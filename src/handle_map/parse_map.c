/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/10 14:36:53 by arabelo-         ###   ########.fr       */
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
	double	x_range;
	double	y_range;
	double	z_range;
	double	max_range;

	x_range = map()->coor->max_x - map()->coor->min_x;
	y_range = map()->coor->max_y - map()->coor->min_y;
	z_range = map()->coor->max_z - map()->coor->min_z;
	max_range = fmax(fmax(x_range,  y_range), z_range);
	map()->sf = fmin(map()->win->win_w / max_range,
		map()->win->win_h / max_range);
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
		current->x *= map()->sf;
		current->y *= map()->sf;
		current->z *= map()->sf;
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
	set_new_max_xy();
	set_new_min_xy();
	set_z_max_min();
	expand_map();
	apply_rotation(map()->coor->angle_x,
		map()->coor->angle_y, map()->coor->angle_z);
	center_map();
}