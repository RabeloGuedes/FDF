/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:57:56 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/19 15:18:30 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_matrix	matrix_infos;
	char		**map;
	int			i;

	i = 0;
	if (ac == 2)
	{
		map = get_matrix(av[1], &matrix_infos);
		// while (map[i])
		// {
		// 	ft_printf("Line %i: %s", i + 1, map[i]);
		// 	i++;
		// }
		window(&matrix_infos);
		free_matrix(map);
	}
	else
		ft_putendl_fd("Error: Usage -> ./fdf \"file_name\"", 2);
	return (0);
}
