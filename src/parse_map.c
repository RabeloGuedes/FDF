/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:45:41 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/21 18:29:16 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	generate_lines(int fd)
{
	char	*line;
	int		lines_amount;
	t_list	*node;

	lines_amount = 0;
	line = get_next_line(fd);
	node = ft_lstnew(line);
	map()->file_begin = node;
	if (!line || !map()->file_begin)
		malloc_error();
	map()->columns_amount = ft_strlen(line);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		node = ft_lstnew(line);
		if (!node)
			malloc_error();
		ft_lstadd_back(&(map()->file_begin), node);
		lines_amount++;
	}
	map()->lines_amount = lines_amount;
}

void	get_matrix(char *file_name)
{
	int		fd;

	fd = handle_open(file_name);
	generate_lines(fd);
	handle_close(fd);
}
