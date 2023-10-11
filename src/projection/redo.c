/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:25:10 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/11 20:16:33 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_projection(bool *changed)
{
	t_node	*head;
	t_node	*prev;

	head = map()->head;
	while (head)
	{
		prev = head;
		while (head)
		{
			head->x = head->origin_x;
			head->y = head->origin_y;
			head->z = head->origin_z;
			head = head->east;
		}
		prev = prev->south;
		head = prev;
	}
	map()->coor->center_switch = 1;
	rebuild_projection();
	center_map();
	*changed = true;
}

void	rebuild_image(void)
{
	ft_bzero(map()->win->addr,
		(map()->win->win_h
			* map()->win->win_w * sizeof(map()->bpp)));
	put_pixels_on_img();
	draw_horizontal_lines();
	draw_vertical_lines();
	mlx_put_image_to_window(map()->win->mlx,
		map()->win->mlx_win, map()->win->img, 0, 0);
}
