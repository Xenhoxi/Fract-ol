/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:14:10 by ljerinec          #+#    #+#             */
/*   Updated: 2023/01/02 16:14:25 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	in_mandelbrot_set(int x0, int y0, int max_iter, t_fractal *fractal)
{
	int			iteration;
	double		cx;
	double		cy;
	double		x_new;

	cx = x0 * fractal->xtt / IMGWIDTH + fractal->x_min;
	cy = y0 * fractal->ytt / IMGHEIGHT + fractal->y_min;
	cx *= fractal->zoom;
	cy *= fractal->zoom;
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