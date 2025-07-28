/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_calculations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:54:25 by mtsubasa          #+#    #+#             */
/*   Updated: 2025/07/28 20:44:03 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	get_escape_value(t_complex z)
{
	return (z.re * z.re + z.im * z.im);
}

int	mandelbrot(t_complex c, int max_iter)
{
	t_complex	z;
	int			i;
	double		escape;
	double		temp;

	z.re = 0.0;
	z.im = 0.0;
	i = 0;
	while (i < max_iter)
	{
		escape = get_escape_value(z);
		if (escape > 4.0)
			return (i);
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = temp;
		i++;
	}
	return (max_iter);
}

int	julia(t_complex c, t_complex z, int max_iter)
{
	int		i;
	double	escape;
	double	temp;

	i = 0;
	while (i < max_iter)
	{
		escape = get_escape_value(z);
		if (escape > 4.0)
			return (i);
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = temp;
		i++;
	}
	return (max_iter);
}

int	burning_ship(t_complex c, int max_iter)
{
	t_complex	z;
	int			i;
	double		escape;
	double		temp;

	z.re = 0.0;
	z.im = 0.0;
	i = 0;
	while (i < max_iter)
	{
		escape = get_escape_value(z);
		if (escape > 4.0)
			return (i);
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * fabs(z.re) * fabs(z.im) + c.im;
		z.re = temp;
		i++;
	}
	return (max_iter);
}
