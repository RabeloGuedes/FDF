/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:18:27 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/19 15:16:06 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	window(t_matrix *matrix_infos)
{
	matrix_infos->mlx = mlx_init();
	matrix_infos->mlx_win = mlx_new_window(matrix_infos->mlx, 1920, 1080, "Hello World!");
	mlx_loop(matrix_infos->mlx);
}