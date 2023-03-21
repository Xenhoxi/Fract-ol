/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:48:53 by ljerinec          #+#    #+#             */
/*   Updated: 2023/03/21 12:06:25 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H

# define FT_FRACTOL_H

# define WIDTH 800
# define HEIGHT 800

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_data {
	mlx_t	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_fractal
{
	char		*set;
	t_data		*mlx;
	double		x;
	double		y;
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	double		cx;
	double		cy;
	double		xtt;
	double		ytt;
	double		zoom;
}		t_fractal;

// sources/fractales/mandelbrot.c
int			in_mandelbrot_set(int x0, int y0, int max_iter, t_fractal *fractal);
void		setup_mandelbrot(t_fractal *fractal);

// sources/fractales/julia.c
int			in_julia_set(int x0, int y0, int max_iter, t_fractal *fractal);
void		setup_julia(t_fractal *fractal, double cx, double cy);

// sources/parsing/parsing.c
void		parsing(int argc, char **argv, t_fractal *fractal);
double		ft_atod(char *str);
void		msg_help(void);

// sources/fract-ol.c
void		init_mlx(t_fractal *f);
void		render_fractal(void *param);
u_int32_t	chose_color(int iteration, int max_iter);

#endif