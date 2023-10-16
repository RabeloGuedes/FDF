/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_projection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:26:43 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/16 17:26:55 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function set the new max and min values
// for x and y, besides expanding the projection
// with the new coordinates
void	rebuild_projection(void)
{
	set_new_max_xy();
	set_new_min_xy();
	expand_map();
}
