/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:50:48 by ljerinec          #+#    #+#             */
/*   Updated: 2023/03/14 14:12:32 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_fractol.h"

void	parsing(int argc, char **argv, t_fractal *fractal)
{
	if (argc < 2)
		msg_help();
	if (!strncmp(argv[1], "mandelbrot", ft_strlen(argv[1])) && argc == 2)
		setup_mandelbrot(fractal);
	else if (!strncmp(argv[1], "Mandelbrot", ft_strlen(argv[1]))
		&& argc == 2)
		setup_mandelbrot(fractal);
	else if (!strncmp(argv[1], "julia", ft_strlen(argv[1])) && argc == 4)
		setup_julia(fractal, ft_atod(argv[2]), ft_atod(argv[3]));
	else
		msg_help();
}

void	msg_help(void)
{
	printf("Paramètres possibles :\n");
	printf("-> Mandelbrot\n");
	printf("-> Julia -0.8 0.156\n");
	exit(1);
}

double	ft_atod(char *str)
{
	int		i;
	double	negatif;
	double	resultat;
	int		u;

	resultat = 0;
	negatif = 1;
	i = 0;
	u = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			negatif = -negatif;
	while (str[i] >= '0' && str[i] <= '9')
		resultat = resultat * 10 + str[i++] - '0';
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		u = u * 10;
		resultat += ((double)str[i++] - '0') / u;
	}
	return (resultat * negatif);
}
