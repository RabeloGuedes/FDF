/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:23:08 by arabelo-          #+#    #+#             */
/*   Updated: 2023/09/27 18:20:31 by arabelo-         ###   ########.fr       */
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
	t_list	*file_begin;
}				t_matrix;

// window
void		window(void);
int			mouse_destroy_window(void);
int			esc_window(int key_code);
// window

// parse maps
void		get_matrix(char *file_name);
void		save_matrix(int fd);
void		generate_lines(int fd);
int			convert_line_into_coordinates(char **array, int y);
void		generate_line_phase_1(char **line, char ***array);
void		generate_line_phase_2(int fd, char **line, char ***array, int *y);
// parse maps

// queue
void		queue_add_node(t_node *node);
void		connect_above_node(t_node *node);
t_node		*shift_layers(int x);
t_node		*search_on_the_right(t_node *node_above, int x);
t_node		*dig_and_search(int y);
// queue

// files management
int			handle_open(char *file_name);
void		handle_close(int fd);
// files management

// utils
t_matrix	*map(void);
void		malloc_error(void);
void		free_split(char **array);
void		check_south(t_node	**head, t_node **previous);
void		check_east(t_node **head, t_node **previous);
void		free_nodes(void);
// utils
#endif
