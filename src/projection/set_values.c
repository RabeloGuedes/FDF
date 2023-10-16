/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ranges.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:44:06 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/16 17:33:47 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function sets the max and min
// values of the z-axis
void	set_z_max_min(void)
{
	t_node	*head;
	t_node	*save;

	head = map()->head;
	save = head;
	if (head)
	{
		map()->coor->max_z = head->z;
		map()->coor->min_z = head->z;
		head = head->east;
	}
	while (head)
	{
		while (head)
		{
			if (head->z > map()->coor->max_z)
				map()->coor->max_z = head->z;
			if (head->z < map()->coor->min_z)
				map()->coor->min_z = head->z;
			head = head->east;
		}
		save = save->south;
		head = save;
	}
}

// This function sets the max values 
// of the x-axis and y-axis
void	set_new_max_xy(void)
{
	t_node	*head;
	t_node	*save;

	head = map()->head;
	save = head;
	if (head)
	{
		map()->coor->max_x = head->x;
		map()->coor->max_y = head->y;
		head = head->east;
	}
	while (head)
	{
		while (head)
		{
			if (head->x > map()->coor->max_x)
				map()->coor->max_x = head->x;
			if (head->y > map()->coor->max_y)
				map()->coor->max_y = head->y;
			head = head->east;
		}
		save = save->south;
		head = save;
	}
}

// This function sets the min values 
// of the x-axis and y-axis
void	set_new_min_xy(void)
{
	t_node	*head;
	t_node	*save;

	head = map()->head;
	save = head;
	if (head)
	{
		map()->coor->min_x = head->x;
		map()->coor->min_y = head->y;
		head = head->east;
	}
	while (head)
	{
		while (head)
		{
			if (head->x < map()->coor->min_x)
				map()->coor->min_x = head->x;
			if (head->y < map()->coor->min_y)
				map()->coor->min_y = head->y;
			head = head->east;
		}
		save = save->south;
		head = save;
	}
}

// This function grats that the
// angle will never exceed the
// range between 0 and 360 degrees
double	rad_clamp(double val)
{
	if (val < 0)
		return (2 * M_PI + val);
	else if (val > 2 * M_PI)
		return (2 * M_PI - val);
	return (val);
}
