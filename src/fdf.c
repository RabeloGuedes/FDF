/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:57:56 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/11 20:13:21 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	static t_coor	coor;

	if (ac == 2)
	{
		if (!file_name_checker(av[1]))
		{
			ft_putendl_fd("Error: File extension is invalid!", 2);
			exit(EXIT_FAILURE);
		}
		window_init();
		map()->coor = &coor;
		map()->coor->center_switch = 1;
		map()->coor->angle_x = 0;
		map()->coor->angle_y = 0;
		map()->coor->angle_z = 0;
		get_matrix(av[1]);
		window();
		free_nodes();
	}
	else
		ft_putendl_fd("Error: Usage -> ./fdf \"file_name\"", 2);
	return (0);
}
