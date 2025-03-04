/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:25:31 by paul              #+#    #+#             */
/*   Updated: 2025/03/04 17:10:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfheader.h"
#include <stdlib.h>

int	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		return (1);
	vars->win = mlx_new_window(vars->mlx, LENGTH, HEIGHT, "./fdf");
	if (vars->win == NULL)
	{
		free_mlx(vars, 1);
		return (1);
	}
	vars->img.img = mlx_new_image(vars->mlx, 8000, 8000);
	if (vars->img.img == NULL)
	{
		free_mlx(vars, 2);
		return (1);
	}
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	if (vars->img.addr == NULL)
	{
		free_mlx(vars, 3);
		return (1);
	}
	return (0);
}

int	press_esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		free_mlx(vars, 3);
		ft_free_all(vars->size_map.ymax, vars->maps, NULL);
		exit(1);
	}
	return (0);
}

int	close_windows(t_vars *vars)
{
	free_mlx(vars, 3);
	ft_free_all(vars->size_map.ymax, vars->maps, NULL);
	exit(1);
	return (0);
}
