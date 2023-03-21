/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:49:41 by ljerinec          #+#    #+#             */
/*   Updated: 2023/03/21 11:49:35 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fractol.h"

void	hook(void *param)
{
	mlx_t		*mlx;
	t_fractal	*fractal;

	fractal = param;
	mlx = fractal->mlx->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		fractal->zoom += 1;
		printf("%f\n", fractal->zoom);
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		fractal->zoom -= 1;
		printf("%f\n", fractal->zoom);
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		fractal->x_min += 0.1;
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		fractal->x_min -= 0.1;
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		fractal->y_min -= 0.1;
		render_fractal(fractal);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		fractal->y_min += 0.1;
		render_fractal(fractal);
	}
}

void	fractal_key_hook(mlx_key_data_t key_datas, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (key_datas.key == MLX_KEY_ESCAPE)
		mlx_close_window(fractal->mlx->mlx);
}

int	main(int argc, char **argv)
{
	t_fractal	*f;

	f = (t_fractal *) malloc(sizeof(t_fractal));
	if (!f)
		exit(1);
	f->mlx = (t_data *) malloc(sizeof(t_data));
	if (!f->mlx)
		exit(1);
	parsing(argc, argv, f);
	mlx_key_hook(f->mlx->mlx, &fractal_key_hook, f);
	render_fractal(f);
	mlx_loop_hook(f->mlx->mlx, &hook, f);
	mlx_loop(f->mlx->mlx);
	return (0);
}

void	init_mlx(t_fractal *f)
{
	f->mlx->mlx = mlx_init(WIDTH, HEIGHT, "Fract-ol", true);
	if (!f->mlx->mlx)
		exit(1);
	f->mlx->win = mlx_new_window(f->mlx->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!f->mlx->win)
		exit(1);
	f->mlx->img = mlx_new_image(f->mlx->mlx, WIDTH, HEIGHT);
	if (!f->mlx->img)
		exit(1);
	mlx_loop(f->mlx->mlx);
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
	while (x0++ < WIDTH)
	{
		while (y0++ < HEIGHT)
		{
			i = in_julia_set(x0, y0, max_iter, fractal);
			mlx_put_pixel(fractal->img, x0, y0, chose_color(i, max_iter));
			i = 0;
		}
		y0 = 0;
	}
	mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
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
