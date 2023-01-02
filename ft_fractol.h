/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:48:53 by ljerinec          #+#    #+#             */
/*   Updated: 2023/01/02 18:40:17 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H

# define FT_FRACTOL_H
# define WIDTH 1280
# define HEIGHT 780
# define IMGWIDTH 1000
# define IMGHEIGHT 680

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_fractal
{
	void	*mlx;
	void	*g_img;
	double	x;
	double	y;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	xtt;
	double	ytt;
	double	zoom;
}		t_fractal;

int			in_mandelbrot_set(int x0, int y0, int max_iter, t_fractal *fractal);
int			in_julia_set(int x0, int y0, int max_iter, t_fractal *fractal);
void		render_fractal(void *param);
u_int32_t	chose_color(int iteration, int max_iter);

#endif