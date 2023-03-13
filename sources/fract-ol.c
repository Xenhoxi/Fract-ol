/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:49:41 by ljerinec          #+#    #+#             */
/*   Updated: 2023/03/13 12:13:54 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fractol.h"

void	hook(void *param)
{
	mlx_t		*mlx;
	t_fractal	*fractal;

	fractal = param;
	mlx = fractal->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		fractal->zoom += 1;
		printf("%f\n", fractal->zoom);
		mlx_delete_image(fractal->mlx, fractal->g_img);
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		fractal->zoom -= 1;
		printf("%f\n", fractal->zoom);
		mlx_delete_image(fractal->mlx, fractal->g_img);
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		fractal->x_min += 0.1;
		mlx_delete_image(fractal->mlx, fractal->g_img);
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		fractal->x_min -= 0.1;
		mlx_delete_image(fractal->mlx, fractal->g_img);
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		fractal->y_min -= 0.1;
		mlx_delete_image(fractal->mlx, fractal->g_img);
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		fractal->y_min += 0.1;
		mlx_delete_image(fractal->mlx, fractal->g_img);
		render_fractal(fractal);
	}
}

void	fractal_key_hook(mlx_key_data_t key_datas, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (key_datas.key == MLX_KEY_ESCAPE)
		mlx_close_window(fractal->mlx);
}

void	setup_mandelbrot(t_fractal *fractal)
{
	fractal->x_min = -2 * fractal->zoom;
	fractal->x_max = 0.47 * fractal->zoom;
	fractal->y_min = -1.12 * fractal->zoom;
	fractal->y_max = 1.12 * fractal->zoom;
	fractal->xtt = fractal->x_max - fractal->x_min;
	fractal->ytt = fractal->y_max - fractal->y_min;
	fractal->g_img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	printf("Structure Mandelbrot OK !");
}

void	setup_julia(t_fractal *fractal)
{
	fractal->x_min = -2;
	fractal->x_max = 2;
	fractal->y_min = -2;
	fractal->y_max = 2;
	fractal->xtt = fractal->x_max - fractal->x_min;
	fractal->ytt = fractal->y_max - fractal->y_min;
	fractal->g_img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	printf("Structure Julia OK !");
}

int	main(void)
{
	mlx_t		*mlx;
	t_fractal	fractal;

	mlx = mlx_init(WIDTH, HEIGHT, "Fract-ol", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	fractal.mlx = mlx;
	fractal.zoom = 1;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	setup_mandelbrot(&fractal);
	// setup_julia(&fractal);
	//render_fractal(&fractal);
	// mlx_loop_hook(mlx, &render_fractal, &fractal);
	mlx_key_hook(mlx, &fractal_key_hook, &fractal);
	mlx_loop_hook(mlx, &hook, &fractal);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}

void	render_fractal(void *param)
{
	t_fractal	*fractal;
	double		x0;
	double		y0;
	int			max_iter;
	int			i;

	fractal = param;
	max_iter = 100;
	i = 0;
	x0 = 0;
	y0 = 0;
	fractal->g_img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	while (x0++ < IMGWIDTH)
	{
		while (y0++ < IMGHEIGHT)
		{
			i = in_mandelbrot_set(x0, y0, max_iter, fractal);
			mlx_put_pixel(fractal->g_img, x0, y0, chose_color(i, max_iter));
			i = 0;
		}
		y0 = 0;
	}
	mlx_image_to_window(fractal->mlx, fractal->g_img, 0, 0);
}

u_int32_t	chose_color(int iteration, int max_iter)
{
	u_int32_t	color;

	if (iteration == max_iter)
		color = 255;
	else
		color = (iteration) * 150000000;
	return (color);
}
