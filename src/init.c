/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:54:31 by mtsubasa          #+#    #+#             */
/*   Updated: 2025/07/28 17:32:23 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fractol_init(t_fractol *f, int type)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		exit(1);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol");
	if (!f->win)
		exit(1);
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
		exit(1);
	f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel,
			&f->line_length, &f->endian);
	f->zoom = 1.0;
	f->offset_x = 0.0;
	f->offset_y = 0.0;
	f->max_iter = MAX_ITER;
	f->color_shift = 0;
	f->fractol_type = type;
	f->julia_c.re = -0.7;
	f->julia_c.im = 0.27015;
	f->mouse_x = WIDTH / 2;
	f->mouse_y = HEIGHT / 2;
}

void	setup_hooks(t_fractol *f)
{
	mlx_hook(f->win, KEY_PRESS, KEY_PRESS_MASK, fractol_handle_key, f);
	mlx_hook(f->win, BUTTON_PRESS, BUTTON_PRESS_MASK, fractol_handle_mouse, f);
	mlx_hook(f->win, MOTION_NOTIFY, POINTER_MOTION_MASK,
		fractol_handle_mouse_move, f);
	mlx_hook(f->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		fractol_close_window, f);
}
