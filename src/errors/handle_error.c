/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:49:05 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/16 20:20:00 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function handles the the memory
// allocation in case the malloc fails
void	malloc_error(void)
{
	ft_putendl_fd("Error: Memory allocation failed! Exiting...", 2);
	free_nodes();
	free_project();
	exit(EXIT_FAILURE);
}
