/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:24:12 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/05 11:33:35 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_destroy_window(void)
{
	mlx_destroy_window(map()->win->mlx, map()->win->mlx_win);
	free_nodes();
	exit(EXIT_SUCCESS);
}
