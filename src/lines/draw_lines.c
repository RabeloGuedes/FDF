/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:10:25 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/13 14:56:33 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int line_color(int first_color, int second_color, float delta)
{
	int color[3];

	color[0] = (float)(first_color >> 16 & 0xFF) * (1.0f - delta)
		+ (float)(second_color >> 16 & 0xFF) * delta;
	color[1] = (float)(first_color >> 8 & 0xFF) * (1.0f - delta)
		+ (float)(second_color >> 8 & 0xFF) * delta;
	color[2] = (float)(first_color & 0xFF) * (1.0f - delta)
		+ (float)(second_color & 0xFF) * delta;
	return (color[0] << 16 | color[1] << 8 | color[2]);
}

void	draw_line(t_node *first, t_node *second)
{
	double	steps;
	double	max_steps;
	int		pixel_color;

	map()->coor->delta_x = second->x - first->x;
	map()->coor->delta_y = second->y - first->y;
	if (fabs((double)map()->coor->delta_x)
		<= fabs((double)map()->coor->delta_y))
		max_steps = fabs((double)map()->coor->delta_y);
	else
		max_steps = fabs((double)map()->coor->delta_x);
	map()->coor->x = first->x;
	map()->coor->y = first->y;
	steps = 0;
	while (++steps <= max_steps)
	{
		pixel_color = line_color(first->color, second->color, steps / max_steps);
		put_pixel(map()->coor->x, map()->coor->y, pixel_color);
		map()->coor->x += (map()->coor->delta_x / max_steps);
		map()->coor->y += (map()->coor->delta_y / max_steps);
	}
}

void	draw_horizontal_lines(void)
{
	t_node	*head;
	t_node	*save;
	t_node	*prev;

	head = map()->head;
	save = head;
	while (head)
	{
		prev = head;
		while (head)
		{
			if (head->east)
				head = head->east;
			else
				break ;
			draw_line(prev, head);
			prev = head;
		}
		head = save->south;
		save = head;
	}
}

void	draw_vertical_lines(void)
{
	t_node	*head;
	t_node	*save;
	t_node	*prev;

	head = map()->head;
	save = head;
	while (head)
	{
		prev = head;
		while (head)
		{
			if (head->south)
				head = head->south;
			else
				break ;
			draw_line(prev, head);
			prev = head;
		}
		head = save->east;
		save = head;
	}
}
