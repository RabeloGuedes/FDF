/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 09:43:50 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/16 17:36:48 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This function checks whether the file name 
// is properly formatted or not
int	file_name_checker(char *file_name)
{
	int	len;

	len = ft_strlen(file_name) - 1;
	if (file_name[len] == 'f' && file_name[len - 1] == 'd'
		&& file_name[len - 2] == 'f' && file_name[len - 3] == '.')
		return (1);
	return (0);
}
