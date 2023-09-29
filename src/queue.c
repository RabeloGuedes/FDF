/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:19:40 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/29 10:23:57 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function searchs for the right line 
// above the created node and returns it.
t_node	*dig_and_search(int y)
{
	t_node	*head;

	head = map()->head;
	while (y - 1 != head->y)
		head = head->south;
	return (head);
}

// This function searchs for the right node at the
// same column as the created node and returns it.
t_node	*search_on_the_right(t_node *node_above, int x)
{
	while (node_above->east && node_above->x < x)
		node_above = node_above->east;
	if (node_above->x != x)
		return (NULL);
	return (node_above);
}

// This function searchs for the right place to
// bind the new created node.
t_node	*shift_layers(int x)
{
	t_node	*head;

	head = map()->head;
	while (head->south)
		head = head->south;
	if (!x)
		return (head);
	while (head->east)
		head = head->east;
	return (head);
}

// This function binds the created
// node with the node above it.
void	connect_above_node(t_node *node)
{
	t_node	*node_above;

	node_above = dig_and_search(node->y);
	node_above = search_on_the_right(node_above, node->x);
	if (!node_above)
		return ;
	node_above->south = node;
}

// This function adds the node to
// the data structure.
void	queue_add_node(t_node *node)
{
	t_node	*head;

	head = map()->head;
	if (!head)
		map()->head = node;
	else
	{
		head = shift_layers(node->x);
		if (!node->x)
			head->south = node;
		else
			head->east = node;
		if (node->y > 0)
			connect_above_node(node);
	}
}
