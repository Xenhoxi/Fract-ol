/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:01:52 by ljerinec          #+#    #+#             */
/*   Updated: 2023/01/03 16:40:01 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	in_julia_set(int x0, int y0, int max_iter, t_fractal *fractal)
{
	int		iteration;
	double	cx;
	double	cy;
	double	x_new;

	cx = -0.8;
	cy = .156;
	fractal->x = x0 * fractal->xtt / IMGWIDTH + fractal->x_min;
	fractal->y = y0 * fractal->ytt / IMGHEIGHT + fractal->y_min;
	iteration = 0;
	while ((fractal->x * fractal->x + fractal->y
			* fractal->y) <= 4 && iteration < max_iter)
	{
		x_new = fractal->x * fractal->x - fractal->y * fractal->y;
		fractal->y = 2 * fractal->x * fractal->y + cy;
		fractal->x = x_new + cx;
		iteration++;
	}
	return (iteration);
}
