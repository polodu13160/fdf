/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:25:31 by paul              #+#    #+#             */
/*   Updated: 2025/02/28 23:47:32 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfheader.h"
#include <stdlib.h>

int	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		return (1); // display init
	vars->win = mlx_new_window(vars->mlx, LENGTH, HEIGHT, "./fdf");
	if (vars->win == NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		return (1);
	}
	vars->img.img = mlx_new_image(vars->mlx, 4000, 4000);
	if (vars->img.img == NULL)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		return (1);
	}
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	if (vars->img.addr == NULL)
	{
		free_mlx(vars);
		return (1);
	}
	return (0);
}

int	press_esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		free_mlx(vars);
		ft_free_all(vars->size_map.ymax, vars->maps, NULL);
		exit(1);
	}
	return (0);
}
int	close_windows(t_vars *vars)
{
	free_mlx(vars);
	ft_free_all(vars->size_map.ymax, vars->maps, NULL);
	exit(1);
	return (0);
}