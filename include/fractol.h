/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:54:20 by mtsubasa          #+#    #+#             */
/*   Updated: 2025/08/02 10:20:49 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* X11 Event constants (defined directly to avoid header dependency) */
# define KEY_PRESS 2
# define BUTTON_PRESS 4
# define MOTION_NOTIFY 6
# define DESTROY_NOTIFY 17

/* X11 Event masks (defined directly to avoid header dependency) */
# define KEY_PRESS_MASK 1L
# define BUTTON_PRESS_MASK 4L
# define POINTER_MOTION_MASK 64L
# define STRUCTURE_NOTIFY_MASK 131072L

/* X11 Key codes (defined directly to avoid header dependency) */
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define UP_KEY 65362
# define DOWN_KEY 65364

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 100
# define ESC ESC_KEY
# define LEFT LEFT_KEY
# define RIGHT RIGHT_KEY
# define UP UP_KEY
# define DOWN DOWN_KEY
# define ZOOM_IN 4
# define ZOOM_OUT 5

/* Julia parameter limits */
# define JULIA_MIN -1000.0
# define JULIA_MAX 1000.0

/*
** Complex number structure (using double)
*/
typedef struct s_complex
{
	double		re;
	double		im;
}				t_complex;

/*
** Fractol rendering context
*/
typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	double		zoom;
	double		offset_x;
	double		offset_y;
	int			max_iter;
	int			color_shift;
	int			fractol_type;
	t_complex	julia_c;
	int			mouse_x;
	int			mouse_y;
}				t_fractol;

/* Main functions */
void			fractol_init(t_fractol *f, int type);
void			fractol_render(t_fractol *f);
int				main(int argc, char **argv);

/* Fractal calculations */
int				mandelbrot(t_complex c, int max_iter);
int				julia(t_complex z, t_complex c, int max_iter);
int				burning_ship(t_complex c, int max_iter);

/* Event handlers */
int				fractol_handle_key(int keycode, t_fractol *f);
int				fractol_handle_mouse(int button, int x, int y, t_fractol *f);
int				fractol_handle_mouse_move(int x, int y, t_fractol *f);
int				fractol_close_window(t_fractol *f);

/* Utils */
void			put_pixel_to_image(t_fractol *f, int x, int y, int color);
int				create_rgb(int r, int g, int b);
void			fractol_shift_colors(t_fractol *f);
int				ft_strcmp(const char *s1, const char *s2);
double			ft_atof(const char *str);
void			print_usage(void);
void			setup_hooks(t_fractol *f);
int				ft_isdigit(int c);

#endif
