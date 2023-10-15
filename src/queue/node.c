/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:48:43 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/15 15:26:33 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function checks a valid color base
int	color_checker(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (ft_strchr(&HEX_TABLE_LOWER[10], color[i]))
			return (1);
		i++;
	}
	i = 0;
	while (color[i])
	{
		if (ft_strchr(&HEX_TABLE_UPPER[10], color[i]))
			return (2);
		i++;
	}
	i = 0;
	while (color[i])
	{
		if (ft_strchr(HEX_TABLE_LOWER, color[i]))
			return (3);
		i++;
	}
	return (0);
}

// This function applies color to the node
int	color_build(char *color)
{
	int	res;

	res = color_checker(color);
	if (res == 1 || res == 3)
		return (ft_atoi_base(color, HEX_TABLE_LOWER));
	else if (res == 2)
		return (ft_atoi_base(color, HEX_TABLE_UPPER));
	return (__UINT32_MAX__);
}

// This function creates a node with the coordenates
t_node	*create_node(int altitude, int x, int y, int color)
{
	static unsigned long long	id;
	t_node						*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->id = id++;
	new->z = altitude;
	new->x = x;
	new->y = y;
	new->origin_x = x;
	new->origin_y = y;
	new->origin_z = altitude;
	new->color = color;
	new->east = NULL;
	new->south = NULL;
	map()->coor->size = id;
	return (new);
}

// This function checks if the node has some color
// to be applied and creates the node with its
// attribuites, as coordinates (x, y z) and color
// as well as add the node into the data structure.
int	build_node(char *str, int x, int y)
{
	char	**altitude_and_color;
	t_node	*new_node;

	altitude_and_color = ft_split(str, ',');
	if (!altitude_and_color)
		return (0);
	if (altitude_and_color[1])
		new_node = create_node(ft_atoi(altitude_and_color[0]), x,
				y, color_build(&altitude_and_color[1][2]));
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
