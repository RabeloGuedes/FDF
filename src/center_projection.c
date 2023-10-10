/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:47:33 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/10 13:47:47 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
