/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:57:44 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/13 15:40:13 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rescale_projection(double sf)
{
	t_node	*head;
	t_node	*save;

	head = map()->head;
	while (head)
	{
		save = head;
		while (head)
		{
			head->x *= sf;
			head->y *= sf;
			head->z *= sf;
			head = head->east;
		}
		save = save->south;
		head = save;
	}
}

void	zoom_controls(bool *changed)
{
	if (map()->keys.zoom_in)
		rescale_projection(1.1);
	else if (map()->keys.zoom_out)
		rescale_projection(0.9);
	else
		return ;
	set_new_max_xy();
	set_new_min_xy();
	if (map()->coor->center_switch)
		center_map();
	*changed = true;
}

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
	else
		return ;
	map()->coor->center_switch = 0;
	*changed = true;
}

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

int	central_control()
{
	bool		changed;

	changed = false;
	rotation_controls(&changed);
	translation_controls(&changed);
	zoom_controls(&changed);
	reset_projection(&changed);
	if (changed)
		rebuild_image();
	return (0);
}

int	handle_keybinds(int key_code, bool pressed)
{
	if (key_code == LINUX_ESC_KEYCODE)
	{
		mlx_destroy_window(map()->win->mlx, map()->win->mlx_win);
		free_nodes();
		exit(EXIT_SUCCESS);
	}
	else if (key_code == KEY_LEFT)
		map()->keys.left = pressed;
	else if (key_code == KEY_RIGHT)
		map()->keys.right = pressed;
	else if (key_code == KEY_DOWN)
		map()->keys.down = pressed;
	else if (key_code == KEY_UP)
		map()->keys.up = pressed;
	else if (key_code == KEY_W)
		map()->keys.w = pressed;
	else if (key_code == KEY_A)
		map()->keys.a = pressed;
	else if (key_code == KEY_D)
		map()->keys.d = pressed;
	else if (key_code == KEY_S)
		map()->keys.s = pressed;
	else if (key_code == KEY_E)
		map()->keys.e = pressed;
	else if (key_code == KEY_Q)
		map()->keys.q = pressed;
	else if (key_code == KEY_ZOOM_IN)
		map()->keys.zoom_in = pressed;
	else if (key_code == KEY_ZOOM_OUT)
		map()->keys.zoom_out = pressed;
	else if (key_code == KEY_RESET)
		map()->keys.reset = pressed;
	return (0);
}

int	on_key_pressed(int key_code)
{
	return (handle_keybinds(key_code, true));
}

int	on_key_released(int key_code)
{
	return (handle_keybinds(key_code, false));
}