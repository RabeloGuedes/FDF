/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/23 13:04:46 by arabelo-         ###   ########.fr       */
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
	{
		if (*array[i] == '\n')
			break ;
		if (!build_node(array[i++], x++, y))
			return (0);
	}
	map()->coor->max_x = x;
	return (1);
}

// This function sets ranges of
// all three axes, x, y, and z
void	set_ranges(void)
{
	double		max_range;
	t_matrix	*map_ref;

	map_ref = map();
	map_ref->coor->range_x = map_ref->coor->max_x - map_ref->coor->min_x;
	map_ref->coor->range_y = map_ref->coor->max_y - map_ref->coor->min_y;
	map_ref->coor->range_z = map_ref->coor->max_z - map_ref->coor->min_z;
	max_range = fmax(map_ref->coor->range_x, map_ref->coor->range_y);
	map_ref->coor->max_range = fmax(max_range, map_ref->coor->range_z);
}

// This function calculates the scale factor
// based on the window's and file's measurements
void	get_scaling_factor(void)
{
	double		ratio_width;
	double		ratio_height;
	t_matrix	*map_ref;

	set_ranges();
	map_ref = map();
	ratio_height = map_ref->win->win_h / map_ref->coor->max_range;
	ratio_width = map_ref->win->win_w / map_ref->coor->max_range;
	map_ref->sf = fmin(ratio_width, ratio_height);
}

// This function calls the scale factor function
// to recalculate the new pixel distribuition
void	expand_map(void)
{
	t_node	*current;
	t_node	*save;

	current = map()->head;
	save = current;
	while (current)
	{
		current->x *= map()->sf / 1.6;
		current->y *= map()->sf / 1.6;
		current->z *= map()->sf / 1.6;
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
	window_init();
	generate_lines(fd);
	handle_close(fd);
	set_new_max_xy();
	set_new_min_xy();
	set_z_max_min();
	get_scaling_factor();
	expand_map();
	apply_rotation(1,
		-0.8, 0.2);
	center_map();
}
