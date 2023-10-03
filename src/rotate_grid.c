/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:30:09 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/03 16:49:45 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_rotation(void)
{
	t_node	*head;
	t_node	*prev;
	int		orig_x;
	int		orig_y;

	head = map()->head;
	while (head)
	{
		prev = head;
		while (head)
		{
			orig_x = head->x;
			orig_y = head->y;
			head->x = (orig_x - orig_y) * cos(0.5);
			head->y = (orig_x + orig_y) * sin(0.5);
			if (head->z != 0)
				head->y -= head->z;
			head = head->east;
		}
		prev = prev->south;
		head = prev;
	}
}