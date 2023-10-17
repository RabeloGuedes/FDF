/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:23:08 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/17 17:45:15 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <stdbool.h>
# include <mlx_int.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>

# ifndef ZOOM_IN_RATIO
#  define ZOOM_IN_RATIO 1.015
# endif

# ifndef ZOOM_OUT_RATIO
#  define ZOOM_OUT_RATIO 0.965
# endif

# ifndef TRANSLATION_RATIO
#  define TRANSLATION_RATIO 5
# endif

# ifndef ROTATION_RATIO
#  define ROTATION_RATIO 0.010
# endif

# ifndef M_PI
#  define M_PI 3.141592653589793
# endif

# ifndef LINUX_ESC_KEYCODE
#  define LINUX_ESC_KEYCODE 65307
# endif

# ifndef KEY_LEFT
#  define KEY_LEFT 65363
# endif

# ifndef KEY_RIGHT
#  define KEY_RIGHT 65361
# endif

# ifndef KEY_DOWN
#  define KEY_DOWN 65364
# endif

# ifndef KEY_UP
#  define KEY_UP 65362
# endif

# ifndef KEY_W
#  define KEY_W 119
# endif

# ifndef KEY_A
#  define KEY_A 97
# endif

# ifndef KEY_D
#  define KEY_D 100
# endif

# ifndef KEY_S
#  define KEY_S 115
# endif

# ifndef KEY_E
#  define KEY_E 101
# endif

# ifndef KEY_Q
#  define KEY_Q 113
# endif

# ifndef KEY_ZOOM_IN
#  define KEY_ZOOM_IN 61
# endif

# ifndef KEY_ZOOM_OUT
#  define KEY_ZOOM_OUT 45
# endif

# ifndef KEY_RESET
#  define KEY_RESET 48
# endif

# ifndef ON_KEYDOWN
#  define ON_KEYDOWN 2
# endif

# ifndef ON_DESTROY
#  define ON_DESTROY 17
# endif

typedef struct s_node
{
	int				id;
	double			x;
	double			y;
	double			z;
	double			origin_x;
	double			origin_y;
	double			origin_z;
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
	double					x;
	double					y;
	double					delta_x;
	double					delta_y;
	double					max_x;
	double					max_y;
	double					max_z;
	double					min_x;
	double					min_y;
	double					min_z;
	double					range_x;
	double					range_y;
	double					range_z;
	double					max_range;
	double					x_center;
	double					y_center;
	unsigned long long		size;
}				t_coor;

typedef struct s_keybinds
{
	bool	left;
	bool	right;
	bool	down;
	bool	up;
	bool	w;
	bool	a;
	bool	d;
	bool	s;
	bool	e;
	bool	q;
	bool	zoom_in;
	bool	zoom_out;
	bool	reset;
}			t_keybinds;

typedef struct s_matrix_infos
{
	int			columns_amount;
	t_win		*win;
	double		sf;
	int			bpp;
	int			endian;
	t_node		*head;
	t_coor		*coor;
	t_keybinds	keys;
}				t_matrix;

// errors
void		malloc_error(void);
int			handle_open(char *file_name);
void		handle_close(int fd);
// errors

// handle_map
void		apply_mod(int set_origin, char direction);
t_matrix	*map(void);
int			convert_line_into_coordinates(char **array, int y);
void		get_scaling_factor(void);
void		expand_map(void);
void		get_matrix(char *file_name);
// handle_map

// lines
void		generate_lines(int fd);
void		generate_line_phase_1(char **line, char ***array);
void		generate_line_phase_2(int fd, char **line, char ***array, int *y);
void		draw_line(t_node *first, t_node *second);
void		draw_horizontal_lines(void);
void		draw_vertical_lines(void);
// lines

// projection
void		center_map_width(double max_x, double min_x);
void		center_map_height(double max_y, double min_y);
void		center_map(void);
void		handle_arrow_keys(int key_code, bool pressed);
void		handle_wasdeq_keys(int key_code, bool pressed);
int			handle_keybinds(int key_code, bool pressed);
int			on_key_pressed(int key_code);
int			on_key_released(int key_code);
int			central_control(void);
void		translation_controls(bool *changed);
void		rotation_controls(bool *changed);
void		rebuild_projection(void);
void		reset_projection(bool *changed);
void		rebuild_image(void);
void		rotate_x(t_node *node, double angle_x);
void		rotate_y(t_node *node, double angle_y);
void		rotate_z(t_node *node, double angle_z);
void		apply_rotation(double angle_x, double angle_y, double angle_z);
void		set_z_max_min(void);
void		set_new_max_xy(void);
void		set_new_min_xy(void);
void		set_ranges(void);
double		rad_clamp(double val);
void		rescale_projection(double sf);
void		calculate_center(double *x_center, double *y_center);
// projection

// queue
int			color_checker(char *color);
int			color_build(char *color);
t_node		*create_node(int altitude, int x, int y, int color);
int			build_node(char *str, int x, int y);
t_node		*dig_and_search(int y);
t_node		*search_on_the_right(t_node *node_above, int x);
t_node		*shift_layers(int x);
void		connect_above_node(t_node *node);
void		queue_add_node(t_node *node);
// queue

// utils
int			file_name_checker(char *file_name);
void		free_split(char **array);
void		check_south(t_node	**head, t_node **previous);
void		check_east(t_node **head, t_node **previous);
void		free_nodes(void);
void		free_project(void);
// utils

// window
void		window_init(void);
void		window(void);
void		put_pixel(int x, int y, int color);
void		put_pixels_on_img(void);
int			mouse_destroy_window(void);
// window

#endif
