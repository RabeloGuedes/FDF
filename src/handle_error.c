/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:49:05 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/21 16:42:40 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	malloc_error(void)
{
	ft_putendl_fd("Error: Memory allocation failed! Exiting...", 2);
	if (map()->file_begin)
		ft_lstclear(&(map()->file_begin), free);
	exit(EXIT_FAILURE);
}
