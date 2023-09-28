/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:48:43 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/28 18:02:06 by arabelo-         ###   ########.fr       */
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
