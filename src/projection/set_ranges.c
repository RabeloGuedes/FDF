/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ranges.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:44:06 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/11 15:27:37 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

double	rad_clamp(double val)
{
	if (val < 0)
		return (2 * M_PI + val);
	else if (val > 2 * M_PI)
		return (2 * M_PI - val);
	return (val);
}
