/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:18:27 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/28 18:51:15 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	window_init(void)
{
	map()->mlx = mlx_init();
	mlx_get_screen_size(map()->mlx, &map()->win_w, &map()->win_h);
}

void	put_pixel(int x, int y, int color)
{
	char	*dst;

	dst = map()->addr + (y * map()->columns_amount
			+ x * (map()->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_pixels_on_img(void)
{
	t_node	*head;
	t_node	*save;

	head = map()->head;
	save = head;
	while (head)
	{
		while (head)
		{
			put_pixel(head->x, head->y, head->color);
			head = head->right;
		}
		save = save->bottom;
		head = save;
	}
}

void	window(void)
{
	t_matrix	*map_ref;

	map_ref = map();
	map_ref->img = mlx_new_image(map_ref->mlx, map_ref->win_w, map_ref->win_h);
	map_ref->mlx_win = mlx_new_window(map_ref->mlx, map_ref->win_w,
			map_ref->win_h, "fdf");
	map_ref->addr = mlx_get_data_addr(map_ref->img, &map_ref->bpp, &map_ref->columns_amount,
			&map_ref->endian);
	put_pixels_on_img();
	mlx_put_image_to_window(map_ref->mlx, map_ref->mlx_win, map_ref->img, 0, 0);
	mlx_hook(map_ref->mlx_win, ON_KEYDOWN, 1L << 0, esc_window, map_ref);
	mlx_hook(map_ref->mlx_win, ON_DESTROY, 0, mouse_destroy_window, map_ref);
	mlx_loop(map_ref->mlx);
}
