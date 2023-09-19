/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:23:08 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/19 15:17:46 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <mlx_int.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>

typedef struct	s_matrix_infos
{
	size_t	lines_amount;
	size_t	columns_amount;
	void	*mlx;
	void	*mlx_win;
}				t_matrix;


// window
void	window(t_matrix *matrix_infos);
// window

// parse maps
char	**get_matrix(char *file_name, t_matrix *matrix_infos);
char	**save_matrix(int fd, t_matrix *matrix_infos);
size_t	count_file_lines(int fd);
// parse maps

// files management
int		handle_open(char *file_name);
void	handle_close(int fd, char **matrix);
// files management

// utils
void	free_matrix(char **matrix);
// utils
#endif
