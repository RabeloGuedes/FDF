/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/27 18:16:34 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function creates a node with the coordenates
t_node	*create_node(int altitude, int x, int y, int color)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->z = altitude;
	new->x = x;
	new->y = y;
	new->color = color;
	new->right = NULL;
	new->bottom = NULL;
	return (new);
}

int	build_node(char *str, int x, int y)
{
	char	**altitude_and_color;
	t_node	*new_node;

	altitude_and_color = ft_split(str, ',');
	if (!altitude_and_color)
		return (0);
	if (altitude_and_color[1])
		new_node = create_node(ft_atoi(altitude_and_color[0]), x,
				y, ft_atoi_base(&altitude_and_color[1][2], HEX_TABLE_LOWER));
	else
		new_node = create_node(ft_atoi(altitude_and_color[0]), x,
				y, 0xffffffff);
	if (!new_node)
	{
		free_split(altitude_and_color);
		return (0);
	}
	queue_add_node(new_node);
	free_split(altitude_and_color);
	return (1);
}

int	convert_line_into_coordinates(char **array, int y)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (array[i])
		if (!build_node(array[i++], x++, y))
			return (0);
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

// Main function to build the data structure
void	get_matrix(char *file_name)
{
	int		fd;

	fd = handle_open(file_name);
	generate_lines(fd);
	handle_close(fd);
	display_nodes();
}
