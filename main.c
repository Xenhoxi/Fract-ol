/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:49:41 by ljerinec          #+#    #+#             */
/*   Updated: 2023/01/02 18:41:22 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "ft_fractol.h"

void	hook(void *param)
{
	mlx_t		*mlx;
	t_fractal	*fractal;
	int static	i = 0;

	fractal = param;
	mlx = fractal->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		fractal->zoom *= .9;
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		fractal->zoom *= 1.1;
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		fractal->x_min += 0.1;
		fractal->x_max += 0.1;
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		fractal->x_min -= 0.1;
		fractal->x_max -= 0.1;
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		fractal->y_min -= 0.1;
		fractal->y_max -= 0.1;
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		fractal->y_min += 0.1;
		fractal->y_max += 0.1;
		render_fractal(fractal);
	}
	printf("%d\n", (i++)%60);
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
	//render_fractal(&fractal);
	// mlx_loop_hook(mlx, &render_fractal, &fractal);
	//mlx_key_hook
	// mlx_keyfunc();
	mlx_loop_hook(mlx, &hook, &fractal);
	system("leaks a.out");//
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}

void	clear_screen(mlx_image_t	*g_img)
{
	int	x0;
	int	y0;

	x0 = 0;
	y0 = 0;
	while (x0++ < IMGWIDTH)
		while (y0 < IMGHEIGHT)
			mlx_put_pixel(g_img, x0, y0, 0);
}

void	render_fractal(void *param)
{
	t_fractal	*fractal;
	mlx_image_t	*g_img;
	double		x0;
	double		y0;
	int			max_iter;
	int			iteration;

	g_img = fractal->g_img;
	fractal = param;
	max_iter = 100;
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
