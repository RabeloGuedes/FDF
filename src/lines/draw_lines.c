/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:10:25 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/17 16:22:44 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function extracts the rgb values based on how far
// the pixel is from both start and end pixel
int	line_color(int first_color, int second_color, float delta)
{
	int		color[3];
	float	diff;

	diff = 1.0 - delta;
	color[0] = (float)(first_color >> 16 & 0xFF) *diff
		+ (float)(second_color >> 16 & 0xFF) *delta;
	color[1] = (float)(first_color >> 8 & 0xFF) *diff
		+ (float)(second_color >> 8 & 0xFF) *delta;
	color[2] = (float)(first_color & 0xFF) *diff
		+ (float)(second_color & 0xFF) *delta;
	return (color[0] << 16 | color[1] << 8 | color[2]);
}

// This function draws a line, pixel by pixel
// starting from the first node to the second
void	draw_line(t_node *first, t_node *second)
{
	double	steps;
	double	max_steps;
	int		pixel_color;
	float	ratio;

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
		ratio = steps / max_steps;
		pixel_color = line_color(first->color, second->color, ratio);
		put_pixel(map()->coor->x, map()->coor->y, pixel_color);
		map()->coor->x += (map()->coor->delta_x / max_steps);
		map()->coor->y += (map()->coor->delta_y / max_steps);
	}
}

// This function draws horizontal lines
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

// This function draws vertical lines
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
