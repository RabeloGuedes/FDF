/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:24:12 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/16 20:04:39 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function destroys the window
// when the cross button of the window
// is pressed
int	mouse_destroy_window(void)
{
	mlx_destroy_window(map()->win->mlx, map()->win->mlx_win);
	free_project();
	free_nodes();
	exit(EXIT_SUCCESS);
}
