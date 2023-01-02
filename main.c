/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:49:41 by ljerinec          #+#    #+#             */
/*   Updated: 2023/01/02 01:29:24 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "ft_fractol.h"
#define WIDTH 1280
#define HEIGHT 720
#define IMGWIDTH 1000
#define IMGHEIGHT 625

int			in_mandelbrot_set(int x0, int y0, int max_iter, t_fractal *fractal);
int			in_julia_set(int x0, int y0, int max_iter);
void		render_fractal(void *param);
u_int32_t	chose_color(int iteration, int max_iter);

void	hook(void *param)
{
	mlx_t		*mlx;
	t_fractal	*fractal;

	fractal = param;
	mlx = fractal->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		fractal->zoom -= 0.1;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		fractal->zoom += 0.1;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		fractal->x_min += 0.1;
		fractal->x_max += 0.1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		fractal->x_min -= 0.1;
		fractal->x_max -= 0.1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		fractal->y_min -= 0.1;
		fractal->y_max -= 0.1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		fractal->y_min += 0.1;
		fractal->y_max += 0.1;
	}
}

void	setup_fractal(t_fractal *fractal)
{
	fractal->x_min = -2;
	fractal->x_max = 0.47;
	fractal->y_min = -1.12;
	fractal->y_max = 1.12;
	fractal->xtt = fractal->x_max - fractal->x_min;
	fractal->ytt = fractal->y_max - fractal->y_min;
	fractal->zoom = 1;
	printf("Structure OK !");
}

int	main(void)
{
	mlx_t		*mlx;
	t_fractal	fractal;

	mlx = mlx_init(WIDTH, HEIGHT, "Fract-ol", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	fractal.mlx = mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	setup_fractal(&fractal);
	mlx_loop_hook(mlx, &render_fractal, &fractal);
	mlx_loop_hook(mlx, &hook, &fractal);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}

void	render_fractal(void *param)
{
	t_fractal	*fractal;
	mlx_image_t	*g_img;
	double		x0;
	double		y0;
	int			max_iter;
	int			iteration;

	fractal = param;
	max_iter = 10;
	iteration = 0;
	x0 = 0;
	y0 = 0;
	g_img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	while (x0++ < IMGWIDTH)
	{
		while (y0++ < IMGHEIGHT)
		{
			iteration = in_mandelbrot_set(x0, y0, max_iter, fractal);
			mlx_put_pixel(g_img, x0, y0, chose_color(iteration, max_iter));
			iteration = 0;
		}
		y0 = 0;
	}
	mlx_image_to_window(fractal->mlx, g_img, 0, 0);
}

u_int32_t	chose_color(int iteration, int max_iter)
{
	u_int32_t	color;

	if (iteration == max_iter)
		color = 255;
	else
		color = (iteration) * 1000000;
	return (color);
}

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

int	in_julia_set(int x0, int y0, int max_iter)
{
	int		iteration;
	double	cx;
	double	cy;
	double	x_new;
	double	x;
	double	y;
	double	Xmin = -2; // Origin = -2 Plan restreint
	double	Xmax = 2; // Origin = 0.75 Plan restreint
	double	Ymin = -2; // Origin = -1.25 Plan restreint
	double	Ymax = 2; // Origin = 1.25 Plan restreint
	double	Xtt = Xmax - Xmin;
	double	Ytt = Ymax - Ymin;

	cx = -0.6;
	cy = 0.2;
	x = x0 * Xtt / IMGWIDTH + Xmin;
	y = y0 * Ytt / IMGHEIGHT + Ymin;
	iteration = 0;
	while ((x * x + y * y) <= 4 && iteration < max_iter)
	{
		x_new = x * x - y * y;
		y = 2 * x * y + cy;
		x = x_new + cx;
		iteration++;
	}
	return (iteration);
}
