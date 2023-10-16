/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:47:33 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/16 17:50:20 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function centers the projection
// in the horizontal screen middle
void	center_map_width(double max_x, double min_x)
{
	int	set_origin;

	set_origin = (map()->win->win_w - max_x - min_x) / 2;
	apply_mod(set_origin, 'x');
}

// This function centers the projection
// in the vertical screen middle
void	center_map_height(double max_y, double min_y)
{
	int	set_origin;

	set_origin = (map()->win->win_h - max_y - min_y) / 2;
	apply_mod(set_origin, 'y');
}

// This function centers the projection
// in the middle of the screen
void	center_map(void)
{
	set_new_max_xy();
	set_new_min_xy();
	center_map_width(map()->coor->max_x, map()->coor->min_x);
	center_map_height(map()->coor->max_y, map()->coor->min_y);
}

// This function calculates the center of
// the projection after it has been moved
void	calculate_center(double *x_center, double *y_center)
{
	double	x_sum;
	double	y_sum;
	t_node	*head;
	t_node	*save;

	x_sum = 0.0;
	y_sum = 0.0;
	head = map()->head;
	save = head;
	while (head)
	{
		while (head)
		{
			x_sum += head->x;
			y_sum += head->y;
			head = head->east;
		}
		save = save->south;
		head = save;
	}
	*x_center = x_sum / map()->coor->size;
	*y_center = y_sum / map()->coor->size;
}
