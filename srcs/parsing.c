/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:50:42 by pde-petr          #+#    #+#             */
/*   Updated: 2025/02/28 23:24:16 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "fdfheader.h"
#include <stdio.h>
#include <stdlib.h>




char	*ft_delete_lf(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[i] = ' ';
	return (line);
}

void	read_line(t_stock_maps **get_line, t_size_map *size_map, int fd,
		t_stock_maps **start)
{
	*size_map = (t_size_map){.xmax = -1, .ymax = 0, .newxmax = 0, .newxmin = 0,
		.newymax = 0, .zoom = 1};
	create_tab_line(size_map, fd, get_line, start);
	close(fd);
	if ((*size_map).ymax == 0)
		exit(1);
	*get_line = *start;
}


int	ft_parsing(int fd, t_point_map ***maps, t_size_map *size_map)
{
	int				y;
	t_stock_maps	*get_line;
	t_stock_maps	*start;

	start = NULL;
	get_line = NULL;
	read_line(&get_line, size_map, fd, &start);
	y = 0;
	*maps = malloc(sizeof(t_point_map *) * (*size_map).ymax);
	if (*maps == NULL)
		exit(1);
	while (start != NULL)
	{
		start->text = ft_delete_lf(start->text);
		(*maps)[y] = conversion_line_to_point(start->text, y, size_map);
		if ((*maps)[y++] == NULL)
		{
			ft_free_all(--y, *maps, start);
			return (1);
		}
		start = get_line->next;
		ft_free_line(get_line);
		get_line = start;
	}
	return (0);
}
