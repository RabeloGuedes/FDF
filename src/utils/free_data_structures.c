/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_structures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:17:58 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/17 14:53:09 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function frees the array elements
// and at the end itself
void	free_split(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			free(array[i++]);
		free(array);
	}
}

// This function searchs for the last line
// and saves the reference at head and previous
void	check_south(t_node	**head, t_node **previous)
{
	*previous = *head;
	while ((*head)->south)
	{
		if ((*head)->south->south)
			*previous = (*head)->south;
		*head = (*head)->south;
	}
	if ((*head)->east)
		*previous = *head;
}

// This function searchs for the last lines node
// and saves the reference at head and previous
void	check_east(t_node **head, t_node **previous)
{
	while ((*head)->east)
	{
		if ((*head)->east->east)
			*previous = (*head)->east;
		*head = (*head)->east;
	}
	if ((*previous)->south == *head)
		(*previous)->south = NULL;
	else if ((*previous)->east == *head)
		(*previous)->east = NULL;
}

// This function runs throughout all nodes
// and free from the last to the first
void	free_nodes(void)
{
	t_node	*head;
	t_node	*previous;

	head = map()->head;
	while (head)
	{
		if (!head->east && !head->south)
		{
			free(head);
			break ;
		}
		check_south(&head, &previous);
		check_east(&head, &previous);
		free(head);
		head = map()->head;
	}
}

// This function free all the 
// memory allocated by mlx
void	free_project(void)
{
	t_matrix	*map_ref;

	map_ref = map();
	if (map_ref->win)
	{
		if (map_ref->win->mlx)
		{
			if (map_ref->win->mlx_win)
				mlx_destroy_window(map_ref->win->mlx, map_ref->win->mlx_win);
			if (map_ref->win->img)
				mlx_destroy_image(map_ref->win->mlx, map_ref->win->img);
			mlx_destroy_display(map_ref->win->mlx);
			free(map_ref->win->mlx);
		}
	}
}
