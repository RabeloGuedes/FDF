/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:22:47 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/29 15:20:05 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	center_map_width(t_node *first, t_node *last)
{
	int	set_origin;

	set_origin = (map()->win->win_w - last->x - first->x) / 2;
	apply_mod(set_origin, 'x');
}

void	center_map_height(t_node *first, t_node *last)
{
	int	set_origin;

	set_origin = (map()->win->win_h - last->y - first->y) / 2;
	apply_mod(set_origin, 'y');
}

void	center_map(void)
{
	t_node	*last;
	t_node	*first;

	last = map()->head;
	first = last;
	while (last->east)
		last = last->east;
	center_map_width(first, last);
	last = first;
	while (last->south)
		last = last->south;
	center_map_height(first, last);
}
