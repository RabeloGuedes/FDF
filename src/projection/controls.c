/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:57:44 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/16 17:50:08 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function applies the zoom effect
// based on the projection center
void	rescale_projection(double sf)
{
	t_node	*head;
	t_node	*save;
	double	x_center;
	double	y_center;

	calculate_center(&x_center, &y_center);
	head = map()->head;
	while (head)
	{
		save = head;
		while (head)
		{
			head->x = (head->x - x_center) * sf + x_center;
			head->y = (head->y - y_center) * sf + y_center;
			head = head->east;
		}
		save = save->south;
		head = save;
	}
}

// This function controls the zoom in and out
void	zoom_controls(bool *changed)
{
	t_node	*head;

	head = map()->head;
	if (map()->keys.zoom_in)
		rescale_projection(1.1);
	else if (map()->keys.zoom_out)
		rescale_projection(0.9);
	else
		return ;
	set_new_max_xy();
	set_new_min_xy();
	*changed = true;
}

// This function controls the translation
void	translation_controls(bool *changed)
{
	if (map()->keys.left)
		apply_mod(50, 'x');
	else if (map()->keys.right)
		apply_mod(-50, 'x');
	else if (map()->keys.down)
		apply_mod(50, 'y');
	else if (map()->keys.up)
		apply_mod(-50, 'y');
	*changed = true;
}

// This function controls the rotations
void	rotation_controls(bool *changed)
{
	double		nangle_x;
	double		nangle_y;
	double		nangle_z;

	nangle_x = map()->coor->angle_x;
	nangle_y = map()->coor->angle_y;
	nangle_z = map()->coor->angle_z;
	if (map()->keys.d)
		nangle_z += 0.1;
	else if (map()->keys.a)
		nangle_z -= 0.1;
	else if (map()->keys.w)
		nangle_x += 0.1;
	else if (map()->keys.s)
		nangle_x -= 0.1;
	else if (map()->keys.q)
		nangle_y -= 0.1;
	else if (map()->keys.e)
		nangle_y += 0.1;
	else
		return ;
	apply_rotation(rad_clamp(nangle_x),
		rad_clamp(nangle_y), rad_clamp(nangle_z));
	center_map();
	*changed = true;
}

// This function handles of other controls
int	central_control(void)
{
	bool		changed;

	changed = false;
	if (map()->keys.d || map()->keys.a
		|| map()->keys.w || map()->keys.s
		|| map()->keys.e || map()->keys.q)
		rotation_controls(&changed);
	else if (map()->keys.up || map()->keys.down
		|| map()->keys.right || map()->keys.left)
	{
		translation_controls(&changed);
		calculate_center(&map()->coor->x_center, &map()->coor->y_center);
	}
	else if (map()->keys.zoom_in || map()->keys.zoom_out)
		zoom_controls(&changed);
	else if (map()->keys.reset)
		reset_projection(&changed);
	if (changed)
		rebuild_image();
	return (0);
}
