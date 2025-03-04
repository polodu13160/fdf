/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:47:49 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/04 15:38:39 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfheader.h"
#include "math.h"
#include <stdlib.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	draw_line(t_point_map **data, t_draw_line info_draw, t_data *img)
{
	info_draw.dx = data[info_draw.y][info_draw.x + 1].z.x
		- data[info_draw.y][info_draw.x].z.x;
	info_draw.dy = data[info_draw.y][info_draw.x + 1].z.y
		- data[info_draw.y][info_draw.x].z.y;
	if (abs(info_draw.dx) > abs(info_draw.dy))
		info_draw.steps = abs(info_draw.dx);
	else
		info_draw.steps = abs(info_draw.dy);
	info_draw.x_inc = info_draw.dx / (float)info_draw.steps;
	info_draw.y_inc = info_draw.dy / (float)info_draw.steps;
	info_draw.x0 = data[info_draw.y][info_draw.x].z.x;
	info_draw.y0 = data[info_draw.y][info_draw.x].z.y;
	info_draw.index = 0;
	while (info_draw.index <= info_draw.steps)
	{
		my_mlx_pixel_put(img, round(info_draw.x0), round(info_draw.y0),
			info_draw.color);
		info_draw.x0 += info_draw.x_inc;
		info_draw.y0 += info_draw.y_inc;
		info_draw.index++;
	}
	return (0);
}

int	draw_line_vertical(t_point_map **data, t_draw_line info_draw, t_data *img)
{
	info_draw.dx = data[info_draw.y + 1][info_draw.x].z.x
		- data[info_draw.y][info_draw.x].z.x;
	info_draw.dy = data[info_draw.y + 1][info_draw.x].z.y
		- data[info_draw.y][info_draw.x].z.y;
	if (abs(info_draw.dx) > abs(info_draw.dy))
		info_draw.steps = abs(info_draw.dx);
	else
		info_draw.steps = abs(info_draw.dy);
	info_draw.x_inc = info_draw.dx / (float)info_draw.steps;
	info_draw.y_inc = info_draw.dy / (float)info_draw.steps;
	info_draw.x0 = data[info_draw.y][info_draw.x].z.x;
	info_draw.y0 = data[info_draw.y][info_draw.x].z.y;
	info_draw.index = 0;
	while (info_draw.index <= info_draw.steps)
	{
		my_mlx_pixel_put(img, round(info_draw.x0), round(info_draw.y0),
			info_draw.color);
		info_draw.x0 += info_draw.x_inc;
		info_draw.y0 += info_draw.y_inc;
		info_draw.index++;
	}
	return (0);
}

void	draw_image(t_vars *vars, int x, int y, t_data *img)
{
	t_draw_line	info_draw;

	info_draw = (t_draw_line){.x = x, .y = y, .color = vars->maps[y][x].color};
	if (x < vars->size_map.xmax - 1)
		draw_line(vars->maps, info_draw, &vars->img);
	if (y < vars->size_map.ymax - 1)
		draw_line_vertical(vars->maps, info_draw, img);
}
