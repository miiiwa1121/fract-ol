/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:54:12 by mtsubasa          #+#    #+#             */
/*   Updated: 2025/07/01 15:54:15 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** handle_key:
**   Handles key events (ESC, arrows, color shift).
*/
int	handle_key(int keycode, t_fractol *f)
{
	double	move_step;

	move_step = 1.0 / f->zoom;
	if (keycode == ESC)
		close_window(f);
	else if (keycode == LEFT)
		f->offset_x -= move_step;
	else if (keycode == RIGHT)
		f->offset_x += move_step;
	else if (keycode == UP)
		f->offset_y -= move_step;
	else if (keycode == DOWN)
		f->offset_y += move_step;
	else if (keycode == 'c' || keycode == 'C')
		shift_colors(f);
	else if (keycode == 'r' || keycode == 'R')
	{
		f->zoom = 1.0;
		f->offset_x = 0.0;
		f->offset_y = 0.0;
		f->color_shift = 0;
	}
	render_fractol(f);
	return (0);
}

/*
** handle_mouse:
**   Handles mouse wheel zoom events at mouse position.
*/
int	handle_mouse(int button, int x, int y, t_fractol *f)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	zoom_factor = 1.5;
	if (button == ZOOM_IN || button == ZOOM_OUT)
	{
		mouse_re = (x - WIDTH / 2.0) * (4.0 / (f->zoom * WIDTH)) + f->offset_x;
		mouse_im = (y - HEIGHT / 2.0) * (4.0 / (f->zoom * HEIGHT))
			+ f->offset_y;
		if (button == ZOOM_IN)
		{
			f->offset_x = mouse_re + (f->offset_x - mouse_re) / zoom_factor;
			f->offset_y = mouse_im + (f->offset_y - mouse_im) / zoom_factor;
			f->zoom *= zoom_factor;
		}
		else if (button == ZOOM_OUT)
		{
			f->offset_x = mouse_re + (f->offset_x - mouse_re) * zoom_factor;
			f->offset_y = mouse_im + (f->offset_y - mouse_im) * zoom_factor;
			f->zoom /= zoom_factor;
		}
		render_fractol(f);
	}
	return (0);
}

/*
** handle_mouse_move:
**   Updates mouse position tracking.
*/
int	handle_mouse_move(int x, int y, t_fractol *f)
{
	f->mouse_x = x;
	f->mouse_y = y;
	return (0);
}

/*
** close_window:
**   Cleans up and exits the program.
*/
int	close_window(t_fractol *f)
{
	if (f->img)
		mlx_destroy_image(f->mlx, f->img);
	if (f->win)
		mlx_destroy_window(f->mlx, f->win);
	if (f->mlx)
	{
		mlx_destroy_display(f->mlx);
		free(f->mlx);
	}
	exit(0);
}

void	shift_colors(t_fractol *f)
{
	f->color_shift += 10;
	if (f->color_shift > 255)
		f->color_shift = 0;
	render_fractol(f);
}
