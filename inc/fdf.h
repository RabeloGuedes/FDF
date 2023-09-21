/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:23:08 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/21 18:28:36 by arabelo-         ###   ########.fr       */
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

typedef struct s_matrix_infos
{
	int		lines_amount;
	int		columns_amount;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		endian;
	t_list	*file_begin;
}				t_matrix;

// window
void		window(void);
// window

// parse maps
void		generate_lines(int fd);
void		get_matrix(char *file_name);
void		save_matrix(int fd);
size_t		count_file_lines(int fd);
// parse maps

// files management
int			handle_open(char *file_name);
void		handle_close(int fd);
// files management

// utils
t_matrix	*map(void);
void		malloc_error(void);
// utils
#endif
