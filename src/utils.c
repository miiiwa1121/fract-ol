/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:54:47 by mtsubasa          #+#    #+#             */
/*   Updated: 2025/07/01 15:54:49 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** ft_strcmp:
**   Compares two strings.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/*
** put_pixel:
**   Draws a pixel at (x, y) with the given color.
*/
void	put_pixel(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/*
** create_rgb:
**   Creates an RGB color from r, g, b values.
*/
int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

/*
** ft_atof:
**   Converts a string to double.
*/

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	frac;

	result = 0.0;
	sign = 1.0;
	frac = 0.1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1.0;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result += (*str++ - '0') * frac;
			frac *= 0.1;
		}
	}
	return (result * sign);
}

/*
** print_usage:
**   Prints usage information.
*/
void	print_usage(void)
{
	write(1, "Usage:\n", 7);
	write(1, "  ./fractol mandelbrot\n", 22);
	write(1, "  ./fractol julia <real> <imaginary>\n", 36);
	write(1, "  ./fractol burning_ship\n", 25);
	write(1, "\nExamples:\n", 11);
	write(1, "  ./fractol julia -0.33 0.67\n", 29);
	write(1, "  ./fractol julia -0.7 0.27015\n", 31);
	write(1, "\nControls:\n", 11);
	write(1, "  ESC: Exit\n", 11);
	write(1, "  Arrow keys: Move\n", 18);
	write(1, "  Mouse wheel: Zoom\n", 20);
	write(1, "  C: Shift colors\n", 17);
	write(1, "  R: Reset view\n", 15);
}
