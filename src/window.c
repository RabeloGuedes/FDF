/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:18:27 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/21 18:26:59 by arabelo-         ###   ########.fr       */
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
	if (map()->columns_amount * map()->bpp > 1920
		|| map()->lines_amount * map()->bpp > 1080)
	{
		map()->img = mlx_new_image(map()->mlx, 1920, 1080);
		map()->mlx_win = mlx_new_window(map()->mlx, 1920, 1080, "fdf");
	}
	else
	{
		map()->img = mlx_new_image(map()->mlx,
			map()->columns_amount * map()->bpp,
			map()->lines_amount * map()->bpp);
		map()->mlx_win = mlx_new_window(map()->mlx,
			map()->columns_amount * map()->bpp,
			map()->lines_amount * map()->bpp, "fdf");
	}
	map()->addr = mlx_get_data_addr(map()->img, &map()->bpp, &map()->columns_amount,
			&map()->endian);
	my_mlx_pixel_put(5, 5, 0x00FF0000);
	mlx_put_image_to_window(map()->mlx, map()->mlx_win, map()->img, 0, 0);
	mlx_loop(map()->mlx);
}