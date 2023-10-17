/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:18:27 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/17 17:41:49 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// It initalizes the window struct
void	window_init(void)
{
	static t_win	window;

	map()->win = &window;
	map()->win->mlx = mlx_init();
	mlx_get_screen_size(map()->win->mlx,
		&map()->win->win_w, &map()->win->win_h);
}

// It draws a pixel on a specific
// coordiantes with a color passed
// as parameter
void	put_pixel(int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < map()->win->win_w && y >= 0 && y < map()->win->win_h)
	{
		dst = map()->win->addr + (y * map()->columns_amount
				+ x * (map()->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

// Draws all the pixels of the projection
// into the image
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
			head = head->east;
		}
		save = save->south;
		head = save;
	}
}

// This is the main function of the 
// window, it configures its behavior
void	window(void)
{
	t_matrix	*map_ref;

	map_ref = map();
	map_ref->win->img = mlx_new_image(map_ref->win->mlx,
			map_ref->win->win_w, map_ref->win->win_h);
	map_ref->win->mlx_win = mlx_new_window(map_ref->win->mlx,
			map_ref->win->win_w, map_ref->win->win_h, "FdF | arabelo-");
	map_ref->win->addr = mlx_get_data_addr(map_ref->win->img,
			&map_ref->bpp, &map_ref->columns_amount, &map_ref->endian);
	put_pixels_on_img();
	draw_horizontal_lines();
	draw_vertical_lines();
	mlx_do_key_autorepeatoff(map()->win->mlx);
	mlx_put_image_to_window(map_ref->win->mlx,
		map_ref->win->mlx_win, map_ref->win->img, 0, 0);
	mlx_hook(map_ref->win->mlx_win, ON_KEYDOWN,
		1L << 0, on_key_pressed, NULL);
	mlx_key_hook(map_ref->win->mlx_win, on_key_released, NULL);
	mlx_hook(map_ref->win->mlx_win, ON_DESTROY, 0,
		mouse_destroy_window, map_ref);
	mlx_loop_hook(map_ref->win->mlx, central_control, NULL);
	mlx_loop(map_ref->win->mlx);
	mlx_loop_end(map()->win->mlx);
}
