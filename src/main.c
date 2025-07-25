/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:54:36 by mtsubasa          #+#    #+#             */
/*   Updated: 2025/07/25 13:01:54 by mtsubasa         ###   ########.fr       */
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

int is_valid_number_str(const char *str)
{
    int i;
    int dot_count;
    int digit_found;

    i = 0;
    dot_count = 0;
    digit_found = 0;
    if (!str || !*str)
        return (0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] == '.')
            dot_count++;
        else if (!ft_isdigit(str[i]))
            return (0);
        if (ft_isdigit(str[i]))
            digit_found = 1;
        i++;
    }
    if (dot_count > 1 || !digit_found)
        return (0);
    return (1);
}

static int	validate_julia_params(int argc, char **argv, t_fractol *f)
{
    if (argc == 4 && is_valid_number_str(argv[2]) && is_valid_number_str(argv[3]))
	{
		f->julia_c.re = ft_atof(argv[2]);
		f->julia_c.im = ft_atof(argv[3]);
		return (1);
	}
	return (0);
}

static int	validate_args(int argc, char **argv, t_fractol *f)
{
	int	type;

	if (argc < 2 || 4 < argc)
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
	fractol_init(&f, type);
	if (type == 2 && argc == 4)
	{
		f.julia_c.re = ft_atof(argv[2]);
		f.julia_c.im = ft_atof(argv[3]);
	}
	setup_hooks(&f);
	fractol_render(&f);
	mlx_loop(f.mlx);
	return (0);
}
