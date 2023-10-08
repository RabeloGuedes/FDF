/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:23:08 by arabelo-          #+#    #+#             */
/*   Updated: 2023/10/08 19:28:56 by arabelo-         ###   ########.fr       */
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

enum
{
	ON_KEYDOWN = 2,
	ON_DESTROY = 17
};

typedef struct s_node
{
	double				x;
	double				y;
	double				z;
	double				origin_x;
	double				origin_y;
	double				origin_z;
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
	double	max_x;
	double	max_y;
	double	max_z;
	double	min_x;
	double	min_y;
	double	min_z;
	double	angle_x;
	double	angle_y;
	double	angle_z;
}				t_coor;

typedef struct s_matrix_infos
{
	int		lines_amount;
	int		columns_amount;
	t_win	*win;
	int		sf_x;
	int		sf_y;
	int		bpp;
	int		endian;
	t_node	*head;
	t_coor	*coor;
}				t_matrix;


// window
void		window(void);
int			mouse_destroy_window(void);
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
void		set_new_max_xy(void);
void		set_new_min_xy(void);
void		set_z_max_min(void);
void		expand_map(void);
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
void		put_pixels_on_img(void);
void		draw_line(t_node *first, t_node *second);
void		draw_horizontal_lines(void);
void		draw_vertical_lines(void);
// draw

// isometrics
void		apply_rotation(double angle_x, double angle_y, double angle_z);
// isometrics

// controls
int			central_control(int key_code);
void		rebuild_image(void);
double		rad_clamp(double val);
void		translation_controls(int key_code, bool *changed);
void		rotation_controls(int key_code, bool *changed);
void		reset_projection(bool *changed);
// controls

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
