/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:57:56 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/23 13:15:34 by arabelo-         ###   ########.fr       */
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
		map()->coor = &coor;
		get_matrix(av[1]);
		window();
		free_nodes();
		free_project();
	}
	else
		ft_putendl_fd("Error: Usage -> ./fdf \"file_name\"", 2);
	return (0);
}
