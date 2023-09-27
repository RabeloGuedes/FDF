/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:24:12 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/27 17:50:46 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_destroy_window(void)
{
	mlx_destroy_window(map()->mlx, map()->mlx_win);
	free_nodes();
	exit(EXIT_SUCCESS);
}

int	esc_window(int key_code)
{
	if (key_code == LINUX_ESC_KEYCODE)
	{
		mlx_destroy_window(map()->mlx, map()->mlx_win);
		free_nodes();
		exit(EXIT_SUCCESS);
	}
	return (0);
}
