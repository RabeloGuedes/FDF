/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:57:56 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/18 15:58:13 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	char	**map;
	int		i;

	i = 0;
	if (ac == 2)
	{
		map = get_matrix(av[1]);
		while (map[i])
		{
			ft_printf("Line %i: %s", i + 1, map[i]);
			i++;
		}
		free_matrix(map);
	}
	else
		ft_putendl_fd("Error: Usage -> ./fdf \"file_name\"", 2);
	return (0);
}
