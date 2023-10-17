/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:09:14 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/17 14:16:24 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function checks if any of
// the arrow keys was pressed or released
void	handle_arrow_keys(int key_code, bool pressed)
{
	if (key_code == KEY_LEFT)
		map()->keys.left = pressed;
	else if (key_code == KEY_RIGHT)
		map()->keys.right = pressed;
	else if (key_code == KEY_DOWN)
		map()->keys.down = pressed;
	else if (key_code == KEY_UP)
		map()->keys.up = pressed;
}

// This function checks if any of
// the wasdeq keys was pressed or released
void	handle_wasdeq_keys(int key_code, bool pressed)
{
	if (key_code == KEY_W)
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
}

// This function checks if any of
// the controls keys was pressed or released
int	handle_keybinds(int key_code, bool pressed)
{
	if (key_code == LINUX_ESC_KEYCODE)
	{
		free_project();
		free_nodes();
		exit(EXIT_SUCCESS);
	}
	else if (key_code == KEY_LEFT || key_code == KEY_RIGHT
		|| key_code == KEY_DOWN || key_code == KEY_UP)
		handle_arrow_keys(key_code, pressed);
	else if (key_code == KEY_W || key_code == KEY_A
		|| key_code == KEY_D || key_code == KEY_S
		|| key_code == KEY_E || key_code == KEY_Q)
		handle_wasdeq_keys(key_code, pressed);
	else if (key_code == KEY_ZOOM_IN)
		map()->keys.zoom_in = pressed;
	else if (key_code == KEY_ZOOM_OUT)
		map()->keys.zoom_out = pressed;
	else if (key_code == KEY_RESET)
		map()->keys.reset = pressed;
	return (0);
}

// This function sets the pressed key state to true
int	on_key_pressed(int key_code)
{
	return (handle_keybinds(key_code, true));
}

// This function sets the released key state to false
int	on_key_released(int key_code)
{
	return (handle_keybinds(key_code, false));
}
