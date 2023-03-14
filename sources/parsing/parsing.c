/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:50:48 by ljerinec          #+#    #+#             */
/*   Updated: 2023/03/13 13:29:47 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_fractol.h"

void	parsing(int argc, char **argv, t_fractal *fractal)
{
	if (strncmp(argv[1], "mandelbrot", ft_strlen(argv[1])) == 0 && argc == 2)
		setup_mandelbrot(fractal);
	if (strncmp(argv[1], "julia", ft_strlen(argv[1])) == 0 && argc != 4)
		msg_help_julia();
	else if (strncmp(argv[1], "julia", ft_strlen(argv[1])) == 0 && argc == 4)
	{

	}
}
