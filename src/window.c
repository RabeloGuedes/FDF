/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:18:27 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/22 16:37:17 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(int x, int y, int color)
{
	char	*dst;

	dst = map()->addr + (y * map()->columns_amount
		+ x * (map()->bpp / 8));
	*(unsigned int*)dst = color;
}

void	window(void)
{
	map()->mlx = mlx_init();
	mlx_get_screen_size(map()->mlx, &map()->win_w, &map()->win_h);
	map()->img = mlx_new_image(map()->mlx, map()->win_w, map()->win_h);
	map()->mlx_win = mlx_new_window(map()->mlx, map()->win_w,
		map()->win_h, "fdf");
	map()->addr = mlx_get_data_addr(map()->img, &map()->bpp, &map()->columns_amount,
			&map()->endian);
	my_mlx_pixel_put(5, 5, 0x00FF0000);
	mlx_put_image_to_window(map()->mlx, map()->mlx_win, map()->img, 0, 0);
	mlx_hook(map()->mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, esc_window, map());
	mlx_hook(map()->mlx_win, ON_DESTROY, 0, mouse_destroy_window, map());
	mlx_loop(map()->mlx);
}