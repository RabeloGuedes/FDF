/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_manipulation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:06:16 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/03 16:12:54 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: File can't be opened, it might not exists! ", 2);
		ft_putendl_fd("Exiting...", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	handle_close(int fd)
{
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error: File can't be closed, it might not exists! ", 2);
		ft_putendl_fd("Exiting...", 2);
		exit(EXIT_FAILURE);
	}
}
