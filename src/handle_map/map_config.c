/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:22:47 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/17 15:56:44 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function applies a new offset along an axis
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
