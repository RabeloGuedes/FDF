/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:30:09 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/16 17:30:26 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function applies the rotation
// the projection along the x-axis 
void	rotate_x(t_node *node, double angle_x)
{
	double	new_y;
	double	new_z;

	new_y = node->y * cos(angle_x) + node->z * -sin(angle_x);
	new_z = node->y * sin(angle_x) + node->z * cos(angle_x);
	node->y = new_y;
	node->z = new_z;
}

// This function applies the rotation
// the projection along the y-axis 
void	rotate_y(t_node *node, double angle_y)
{
	double	new_x;
	double	new_z;

	new_x = node->x * cos(angle_y) + node->z * sin(angle_y);
	new_z = node->x * -sin(angle_y) + node->z * cos(angle_y);
	node->x = new_x;
	node->z = new_z;
}

// This function applies the rotation
// the projection along the z-axis 
void	rotate_z(t_node *node, double angle_z)
{
	double	new_x;
	double	new_y;

	new_x = node->x * cos(angle_z) + node->y * -sin(angle_z);
	new_y = node->x * sin(angle_z) + node->y * cos(angle_z);
	node->x = new_x;
	node->y = new_y;
}

// This function applies the rotations along the 3
// possible axes, x, y, and z
void	apply_rotation(double angle_x, double angle_y, double angle_z)
{
	t_node	*head;
	t_node	*prev;

	head = map()->head;
	while (head)
	{
		prev = head;
		while (head)
		{
			rotate_x(head, angle_x);
			rotate_y(head, angle_y);
			rotate_z(head, angle_z);
			head = head->east;
		}
		prev = prev->south;
		head = prev;
	}
}
