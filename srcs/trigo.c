/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:27:59 by paul              #+#    #+#             */
/*   Updated: 2025/02/28 23:48:14 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfheader.h"
#include <math.h>

void	ft_trigo(t_point_map **maps, t_size_map *size_map, int xmin, int ymin);

void	ft_recurs_trigo(t_point_map **maps, t_size_map *size_map)
{
	while (1)
	{
		size_map->zoom += 0.1;
		ft_trigo(maps, size_map, 0, 0);
		if (size_map->newxmin < 0)
			size_map->newxmin = -size_map->newxmin;
		if (size_map->newymin < 0)
			size_map->newymin = -size_map->newymin;
		ft_trigo(maps, size_map, size_map->newxmin + 10, size_map->newymin
			+ 10);
		if (size_map->newxmax > LENGTH || size_map->newymax > HEIGHT)
		{
			if (size_map->zoom == 1)
				break ;
			size_map->zoom -= 0.1;
			ft_trigo(maps, size_map, 0, 0);
			if (size_map->newxmin < 0)
				size_map->newxmin = -size_map->newxmin;
			if (size_map->newymin < 0)
				size_map->newymin = -size_map->newymin;
			ft_trigo(maps, size_map, size_map->newxmin + 10, size_map->newymin
				+ 10);
			break ;
		}
	}
}

void	redefine_small_and_big_xy(t_point_map **maps, t_size_map *size_map,
		int x, int y)
{
	if ((x == 0 && y == 0) || maps[y][x].z.x < size_map->newxmin)
		size_map->newxmin = maps[y][x].z.x;
	if ((x == 0 && y == 0) || maps[y][x].z.x > size_map->newxmax)
		size_map->newxmax = maps[y][x].z.x;
	if ((x == 0 && y == 0) || maps[y][x].z.y < size_map->newymin)
		size_map->newymin = maps[y][x].z.y;
	if ((x == 0 && y == 0) || maps[y][x].z.y > size_map->newymax)
		size_map->newymax = maps[y][x].z.y;
}

void	ft_trigo(t_point_map **maps, t_size_map *size_map, int xmin, int ymin)
{
	int			y;
	int			x;
	static int	init = 0;

	y = -1;
	while (++y < size_map->ymax)
	{
		x = -1;
		while (++x < size_map->xmax)
		{
			maps[y][x].z.x = (maps[y][x].x * size_map->zoom) * cos(ANGLE)
				+ (maps[y][x].y * size_map->zoom) * cos(ANGLE + 2)
				+ (maps[y][x].z.z) * cos(ANGLE - 2) + xmin;
			maps[y][x].z.y = (maps[y][x].x * size_map->zoom) * sin(ANGLE)
				+ (maps[y][x].y * size_map->zoom) * sin(ANGLE + 2)
				+ (maps[y][x].z.z) * sin(ANGLE - 2) + ymin;
			redefine_small_and_big_xy(maps, size_map, x, y);
		}
	}
	if (init++ == 0)
		ft_recurs_trigo(maps, size_map);
}
