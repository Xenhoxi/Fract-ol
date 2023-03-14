/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:14:10 by ljerinec          #+#    #+#             */
/*   Updated: 2023/03/14 14:50:38 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_fractol.h"

int	in_mandelbrot_set(int x0, int y0, int max_iter, t_fractal *fractal)
{
	int			iteration;
	double		cx;
	double		cy;
	double		x_new;

	cx = x0 * fractal->xtt / IMGWIDTH + fractal->x_min;
	cy = y0 * fractal->ytt / IMGHEIGHT + fractal->y_min;
	fractal->x = 0;
	fractal->y = 0;
	iteration = 0;
	while ((fractal->x * fractal->x
			+ fractal->y * fractal->y) <= 4 && iteration < max_iter)
	{
		x_new = fractal->x * fractal->x - fractal->y * fractal->y + cx;
		fractal->y = 2 * fractal->x * fractal->y + cy;
		fractal->x = x_new;
		iteration++;
	}
	return (iteration);
}

void	setup_mandelbrot(t_fractal *fractal)
{
	fractal->x_min = -2 * fractal->zoom;
	fractal->x_max = 0.47 * fractal->zoom;
	fractal->y_min = -1.12 * fractal->zoom;
	fractal->y_max = 1.12 * fractal->zoom;
	fractal->cx = 0;
	fractal->cy = 0;
	fractal->xtt = fractal->x_max - fractal->x_min;
	fractal->ytt = fractal->y_max - fractal->y_min;
	fractal->g_img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
}
