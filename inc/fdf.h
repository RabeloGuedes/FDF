/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:23:08 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/03 16:12:33 by arabelo-         ###   ########.fr       */
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
	struct s_node	*east;
	struct s_node	*south;
}			t_node;

typedef struct s_window_infos
{
	int		win_h;
	int		win_w;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
}				t_win;

typedef struct s_coor
{
	double	x;
	double	y;
	double	delta_x;
	double	delta_y;
	int		max_x;
	int		max_y;
	int		max_z;
	int		min_x;
	int		min_y;
	int		min_z;
}				t_coor;

typedef struct s_matrix_infos
{
	int		lines_amount;
	int		columns_amount;
	t_win	*win;
	int		sf;
	int		bpp;
	int		endian;
	t_node	*head;
	t_coor	*coor;
}				t_matrix;


// window
void		window(void);
int			mouse_destroy_window(void);
int			esc_window(int key_code);
void		window_init(void);
// window

// parse maps
void		get_matrix(char *file_name);
void		generate_lines(int fd);
int			convert_line_into_coordinates(char **array, int y);
void		generate_line_phase_1(char **line, char ***array);
void		generate_line_phase_2(int fd, char **line, char ***array, int *y);
void		center_map(void);
void		center_map_height(double max_y, double min_y);
void		center_map_width(double max_x, double min_x);
void		apply_mod(int set_origin, char direction);
void		set_new_max_xyz(void);
void		set_new_min_xyz(void);
// parse maps

// queue
t_node		*create_node(int altitude, int x, int y, int color);
int			build_node(char *str, int x, int y);
void		queue_add_node(t_node *node);
void		connect_above_node(t_node *node);
t_node		*shift_layers(int x);
t_node		*search_on_the_right(t_node *node_above, int x);
t_node		*dig_and_search(int y);
// queue

// draw
void		put_pixel(int x, int y, int color);
void		draw_line(t_node *first, t_node *second);
void		draw_horizontal_lines(void);
void		draw_vertical_lines(void);
// draw

// isometrics
void		apply_rotation(void);
// isometrics

// files management
int			handle_open(char *file_name);
void		handle_close(int fd);
// files management

// utils
t_matrix	*map(void);
int			file_name_checker(char *file_name);
void		malloc_error(void);
void		free_split(char **array);
void		check_south(t_node	**head, t_node **previous);
void		check_east(t_node **head, t_node **previous);
void		free_nodes(void);
// utils
#endif
