/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_structures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:17:58 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/27 17:47:55 by arabelo-         ###   ########.fr       */
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
	while ((*head)->bottom)
	{
		if ((*head)->bottom->bottom)
			*previous = (*head)->bottom;
		*head = (*head)->bottom;
	}
	if ((*head)->right)
		*previous = *head;
}

void	check_east(t_node **head, t_node **previous)
{
	while ((*head)->right)
	{
		if ((*head)->right->right)
			*previous = (*head)->right;
		*head = (*head)->right;
	}
	if ((*previous)->bottom == *head)
		(*previous)->bottom = NULL;
	else if ((*previous)->right == *head)
		(*previous)->right = NULL;
}

void	free_nodes(void)
{
	t_node	*head;
	t_node	*previous;

	head = map()->head;
	while (head)
	{
		if (!head->right && !head->bottom)
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
