/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:54:42 by mtsubasa          #+#    #+#             */
/*   Updated: 2025/07/28 17:33:07 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	put_color(t_fractol *f, int iter, int x, int y)
{
	int	color;
	int	r;
	int	g;
	int	b;

	if (iter == f->max_iter)
		color = 0x000000;
	else
	{
		r = (int)(sin(0.1 * iter + f->color_shift) * 127 + 128);
		g = (int)(cos(0.1 * iter + f->color_shift) * 127 + 128);
		b = (int)(sin(0.1 * iter + f->color_shift + 3) * 127 + 128);
		color = create_rgb(r, g, b);
	}
	put_pixel_to_image(f, x, y, color);
}

static void	render_pixel(t_fractol *f, t_complex c, int x, int y)
{
	int	iter;

	if (f->fractol_type == 1)
		iter = mandelbrot(c, f->max_iter);
	else if (f->fractol_type == 2)
		iter = julia(c, f->julia_c, f->max_iter);
	else
		iter = burning_ship(c, f->max_iter);
	put_color(f, iter, x, y);
}

void	fractol_render(t_fractol *f)
{
	int			x;
	int			y;
	t_complex	c;
	double		scale;

	scale = 4.0 / (f->zoom * WIDTH);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c.re = (x - WIDTH / 2) * scale + f->offset_x;
			c.im = (y - HEIGHT / 2) * scale + f->offset_y;
			render_pixel(f, c, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
