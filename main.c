/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:54:36 by mtsubasa          #+#    #+#             */
/*   Updated: 2025/07/01 15:54:38 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_fractol_type(char *arg)
{
	if (!ft_strcmp(arg, "mandelbrot"))
		return (1);
	if (!ft_strcmp(arg, "julia"))
		return (2);
	if (!ft_strcmp(arg, "burning_ship"))
		return (3);
	return (0);
}

static int	validate_julia_params(int argc, char **argv, t_fractol *f)
{
	if (argc == 4)
	{
		f->julia_c.re = ft_atof(argv[2]);
		f->julia_c.im = ft_atof(argv[3]);
		return (1);
	}
	return (0);
}

static void	setup_hooks(t_fractol *f)
{
	mlx_hook(f->win, KEY_PRESS, KEY_PRESS_MASK, handle_key, f);
	mlx_hook(f->win, BUTTON_PRESS, BUTTON_PRESS_MASK, handle_mouse, f);
	mlx_hook(f->win, MOTION_NOTIFY, POINTER_MOTION_MASK, handle_mouse_move, f);
	mlx_hook(f->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, close_window, f);
}

static int	validate_args(int argc, char **argv, t_fractol *f)
{
	int	type;

	if (argc < 2 || argc > 4)
	{
		print_usage();
		return (-1);
	}
	type = get_fractol_type(argv[1]);
	if (!type)
	{
		print_usage();
		return (-1);
	}
	if (type == 2 && !validate_julia_params(argc, argv, f))
	{
		print_usage();
		return (-1);
	}
	return (type);
}

int	main(int argc, char **argv)
{
	t_fractol	f;
	int			type;

	type = validate_args(argc, argv, &f);
	if (type == -1)
		return (1);
	init_fractol(&f, type);
	if (type == 2 && argc == 4)
	{
		f.julia_c.re = ft_atof(argv[2]);
		f.julia_c.im = ft_atof(argv[3]);
	}
	setup_hooks(&f);
	render_fractol(&f);
	mlx_loop(f.mlx);
	return (0);
}
