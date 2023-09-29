/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/29 10:23:57 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function takes an array of strings
// and converts the values of each element
// into integers and put inside a node.
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
			head = head->east;
		}
		save = save->south;
		head = save;
		ft_printf("\n");
	}
}

// This function calculates the scale factor
// based on the window's and file's measurements
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

// This function calls the scale factor function
// to recalculate the new pixel distribuition
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
		if (!current->east)
		{
			save = save->south;
			current = save;
		}
		else
			current = current->east;
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
