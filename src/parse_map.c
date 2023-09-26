/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/26 17:44:51 by arabelo-         ###   ########.fr       */
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
	new->right = NULL;
	new->bottom = NULL;
	return (new);
}

// This function searchs for the right line 
// above the created node and returns it.
t_node	*dig_and_search(int y)
{
	t_node	*head;

	head = map()->head;
	while (y - 1 != head->y)
		head = head->bottom;
	return (head);
}

// This function searchs for the right node at the
// same column as the created node and returns it.
t_node	*search_on_the_right(t_node *node_above, int x)
{
	while (node_above->right && node_above->x < x)
		node_above = node_above->right;
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
	while (head->bottom)
		head = head->bottom;
	if (!x)
		return (head);
	while (head->right)
		head = head->right;
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
	node_above->bottom = node;
}

// This function adds the node to
// the data structure.
void	queue_add_node(t_node *node)
{
	t_node	*head;

	head = map()->head;
	if (!head)
	{
		map()->head = node;
		map()->tail = node;
	}
	else
	{
		head = shift_layers(node->x);
		if (!node->x)
			head->bottom = node;
		else
			head->right = node;
		if (node->y > 0)
			connect_above_node(node);
	}
}

int	build_node(char *str, int x, int y)
{
	char	**altitude_and_color;
	t_node	*new_node;

	altitude_and_color = ft_split(str, ',');
	if (!altitude_and_color)
	{

	}
		return (0);
	if (altitude_and_color[1])
		new_node = create_node(ft_atoi(altitude_and_color[0]), x,
			y, ft_atoi_base(&altitude_and_color[1][2], HEX_TABLE_LOWER));
	else
		new_node = create_node(ft_atoi(altitude_and_color[0]), x,
			y, 0);
	if (!new_node)
	{
		malloc_error();
		return (0);
	}
	queue_add_node(new_node);
	free_split(array);
	return (1);
}

void	convert_line_into_coordinates(char **array, int y)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (array[i])
	{
		build_node(array[i], x++, y);
	}
}

void	generate_lines(int fd)
{
	char	*line;
	char	**array;
	int		y;

	line = get_next_line(fd);
	if (!line)
		return ;
	array = ft_split(line, ' ');
	y = 0;
	while (line)
	{
		if (!array)
		{
			free(line);
			free_nodes();
			malloc_error();
		}
		free(line);
		convert_line_into_coordinates(array, y++);
		free_split(array);
		line = get_next_line(fd);
		array = ft_split(line, ' ');
	}
	free(line);
	free_split(array);
}

// Deprecated
// void	generate_lines(int fd)
// {
// 	char	*line;
// 	int		lines_amount;
// 	t_list	*node;

// 	lines_amount = 0;
// 	line = get_next_line(fd);
// 	node = ft_lstnew(line);
// 	map()->file_begin = node;
// 	if (!line || !map()->file_begin)
// 		malloc_error();
// 	map()->columns_amount = ft_strlen(line);
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		node = ft_lstnew(line);
// 		if (!node)
// 			malloc_error();
// 		ft_lstadd_back(&(map()->file_begin), node);
// 		lines_amount++;
// 	}
// 	map()->lines_amount = lines_amount;
// }

// Main function to build the data structure
void	get_matrix(char *file_name)
{
	int		fd;

	fd = handle_open(file_name);
	generate_lines(fd);
	handle_close(fd);
}
