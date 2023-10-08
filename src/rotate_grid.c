/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:30:09 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/08 19:34:57 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_rotation(double angle_x, double angle_y, double angle_z)
{
	t_node	*head;
	t_node	*prev;
	double		new_x;
	double		new_y;
	double		new_z;
	
	head = map()->head;
	while (head)
	{
		prev = head;
		while (head)
		{
			new_y = head->y * cos(angle_x) + head->z * -sin(angle_x);
			new_z = head->y * sin(angle_x) + head->z * cos(angle_x);

			head->x = head->x * cos(angle_y) + new_z * sin(angle_y);
			head->z = head->x * -sin(angle_y) + new_z * cos(angle_y);
			
			new_x = head->x * cos(angle_z) + new_y * -sin(angle_z);
			new_y = head->x * sin(angle_z) + new_y * cos(angle_z);

			head->x = new_x;
			head->y = new_y;
			head->z = new_z;
			head = head->east;
		}
		prev = prev->south;
		head = prev;
	}
}