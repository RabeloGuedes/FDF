/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_structures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:17:58 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/29 10:23:57 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
