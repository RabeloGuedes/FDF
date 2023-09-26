/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:23:08 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/26 17:52:20 by arabelo-         ###   ########.fr       */
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

# ifndef LINUX_ESC_KEYCODE
#  define LINUX_ESC_KEYCODE 65307
# endif

# ifndef KEY_PRESS_MASK
#  define KEY_PRESS_MASK 1L<<0
# endif

enum
{
	ON_KEYDOWN = 2,
	ON_DESTROY = 17
};

typedef struct s_node
{
	int				x;
	int				y;
	int				z;
	long long		color;
	struct s_node	*right;
	struct s_node	*bottom;
}			t_node;

typedef struct s_matrix_infos
{
	int		lines_amount;
	int		columns_amount;
	int		win_h;
	int		win_w;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		endian;
	t_node	*head;
	t_node	*tail;
	t_list	*file_begin;
}				t_matrix;

// window
void		window(void);
int			mouse_destroy_window(void);
int			esc_window(int key_code);
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
void		free_split(char **array);
void		free_nodes(void);
// utils
#endif
