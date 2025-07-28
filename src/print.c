/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:33:46 by mtsubasa          #+#    #+#             */
/*   Updated: 2025/07/28 17:33:48 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
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
