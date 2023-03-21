/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:01:52 by ljerinec          #+#    #+#             */
/*   Updated: 2023/03/17 10:44:39 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_fractol.h"

int	in_julia_set(int x0, int y0, int max_iter, t_fractal *fractal)
{
	int		iteration;
	double	cx;
	double	cy;
	double	x_new;

	fractal->x = x0 * fractal->xtt / WIDTH + fractal->x_min;
	fractal->y = y0 * fractal->ytt / HEIGHT + fractal->y_min;
	iteration = 0;
	while ((fractal->x * fractal->x + fractal->y
			* fractal->y) <= 4 && iteration < max_iter)
	{
		x_new = fractal->x * fractal->x - fractal->y * fractal->y;
		fractal->y = 2 * fractal->x * fractal->y + fractal->cy;
		fractal->x = x_new + fractal->cx;
		iteration++;
	}
	return (iteration);
}

void	setup_julia(t_fractal *fractal, double cx, double cy)
{
	fractal->name = "Julia";
	fractal->x_min = -2;
	fractal->x_max = 2;
	fractal->y_min = -2;
	fractal->y_max = 2;
	fractal->cx = cx;
	fractal->cy = cy;
	fractal->xtt = fractal->x_max - fractal->x_min;
	fractal->ytt = fractal->y_max - fractal->y_min;
}
