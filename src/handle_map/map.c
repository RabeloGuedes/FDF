/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:32:49 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/16 16:35:51 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function return the reference/address of a static struct
t_matrix	*map(void)
{
	static t_matrix	map;

	map.bpp = 32;
	return (&map);
}
