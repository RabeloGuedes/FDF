/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/28 18:00:21 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	convert_line_into_coordinates(char **array, int y)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (array[i])
		if (!build_node(array[i++], x++, y))
			return (0);
	map()->columns_amount = x;
	return (1);
}

void	display_nodes(void)
{
	t_node	*head;
	t_node	*save;

	head = map()->head;
	save = head;
	while (head)
	{
		while (head)
		{
			ft_printf("(%i, %i, %i) -> ", head->x, head->y, head->z);
			head = head->right;
		}
		save = save->bottom;
		head = save;
		ft_printf("\n");
	}
}

void	get_scaling_factor(void)
{
	int	map_h;
	int	map_w;
	int	sf_h;
	int	sf_w;

	map_h = map()->lines_amount;
	map_w = map()->columns_amount;
	sf_h = map()->win_h / map_h;
	sf_w = map()->win_w / map_w;
	if (sf_w < sf_h)
		map()->sf = sf_w;
	else
		map()->sf = sf_h;
}

void	expand_map(void)
{
	t_node	*current;
	t_node	*save;

	get_scaling_factor();
	current = map()->head;
	save = current;
	while (current)
	{
		current->x *= map()->sf / 1.6;
		current->y *= map()->sf / 1.6;
		if (!current->right)
		{
			save = save->bottom;
			current = save;
		}
		else
			current = current->right;
	}
}

// Main function to build the data structure
void	get_matrix(char *file_name)
{
	int		fd;

	fd = handle_open(file_name);
	generate_lines(fd);
	handle_close(fd);
	expand_map();
}
