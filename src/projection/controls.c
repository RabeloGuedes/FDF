/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:57:44 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/11 15:27:23 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translation_controls(int key_code, bool *changed)
{
	if (key_code == KEY_LEFT)
		apply_mod(5, 'x');
	if (key_code == KEY_RIGHT)
		apply_mod(-5, 'x');
	if (key_code == KEY_DOWN)
		apply_mod(5, 'y');
	if (key_code == KEY_UP)
		apply_mod(-5, 'y');
	*changed = true;
}

void	rotation_controls(int key_code, bool *changed)
{
	double		nangle_x;
	double		nangle_y;
	double		nangle_z;

	nangle_x = map()->coor->angle_x;
	nangle_y = map()->coor->angle_y;
	nangle_z = map()->coor->angle_z;
	if (key_code == KEY_D)
		nangle_z += 0.1;
	if (key_code == KEY_A)
		nangle_z -= 0.1;
	if (key_code == KEY_W)
		nangle_x += 0.1;
	if (key_code == KEY_S)
		nangle_x -= 0.1;
	if (key_code == KEY_Q)
		nangle_y -= 0.1;
	if (key_code == KEY_E)
		nangle_y += 0.1;
	apply_rotation(rad_clamp(nangle_x),
		rad_clamp(nangle_y), rad_clamp(nangle_z));
	center_map();
	*changed = true;
}

int	central_control(int key_code)
{
	bool		changed;

	if (key_code == LINUX_ESC_KEYCODE)
	{
		mlx_destroy_window(map()->win->mlx, map()->win->mlx_win);
		free_nodes();
		exit(EXIT_SUCCESS);
	}
	changed = false;
	if (key_code == KEY_D || key_code == KEY_A
		|| key_code == KEY_W || key_code == KEY_S
		|| key_code == KEY_E || key_code == KEY_Q)
		rotation_controls(key_code, &changed);
	if (key_code == KEY_UP || key_code == KEY_DOWN
		|| key_code == KEY_RIGHT || key_code == KEY_LEFT)
		translation_controls(key_code, &changed);
	if (key_code == KEY_RESET)
		reset_projection(&changed);
	if (changed)
		rebuild_image();
	return (0);
}
