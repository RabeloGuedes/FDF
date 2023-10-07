/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:22:47 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/05 12:35:29 by arabelo-         ###   ########.fr       */
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

void	apply_mod(int set_origin, char direction)
{
	t_node	*head;
	t_node	*previous;

	head = map()->head;
	previous = head;
	while (head)
	{
		while (head)
		{
			if (direction == 'x')
				head->x += set_origin;
			else
				head->y += set_origin;
			head = head->east;
		}
		head = previous->south;
		previous = head;
	}
}

void	center_map_width(double max_x, double min_x)
{
	int	set_origin;

	set_origin = (map()->win->win_w - max_x - min_x) / 2;
	apply_mod(set_origin, 'x');
}

void	center_map_height(double max_y, double min_y)
{
	int	set_origin;

	set_origin = (map()->win->win_h - max_y - min_y) / 2;
	apply_mod(set_origin, 'y');
}

void	center_map(void)
{
	set_new_max_xy();
	set_new_min_xy();
	center_map_width(map()->coor->max_x, map()->coor->min_x);
	center_map_height(map()->coor->max_y, map()->coor->min_y);
}
