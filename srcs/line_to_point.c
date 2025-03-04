/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:23:35 by paul              #+#    #+#             */
/*   Updated: 2025/03/04 15:40:18 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfheader.h"
#include <stdlib.h>

void	create_list(t_stock_maps **get_line, t_size_map *size,
		t_stock_maps **start, int fd)
{
	while (1)
	{
		(*get_line)->next = malloc(sizeof(t_stock_maps));
		if ((*get_line)->next == NULL)
		{
			ft_free_list(*start);
			size->ymax = 0;
			return ;
		}
		(*get_line)->next->text = get_next_line(fd);
		if ((*get_line)->next->text == NULL)
		{
			free((*get_line)->next);
			(*get_line)->next = NULL;
			break ;
		}
		else
			*get_line = (*get_line)->next;
		size->ymax++;
	}
}

void	create_tab_line(t_size_map *size, int fd, t_stock_maps **get_line,
		t_stock_maps **start)
{
	(*get_line) = malloc(sizeof(t_stock_maps));
	if (get_line == NULL)
		return ;
	(*get_line)->next = NULL;
	(*get_line)->text = get_next_line(fd);
	if ((*get_line)->text == NULL)
	{
		free(*get_line);
		exit(0);
	}
	(*start) = *get_line;
	size->ymax++;
	create_list(get_line, size, start, fd);
}

t_point_map	*ft_create_t_line(char ***parse_line, char *line, int *size_line,
		t_size_map *size_map)
{
	t_point_map	*t_line;

	(*parse_line) = ft_split(line, ' ');
	if (*parse_line == NULL)
		return (NULL);
	*size_line = size_tab(*parse_line);
	if (size_map->xmax == -1)
		size_map->xmax = *size_line;
	if (size_map->xmax != *size_line)
		return (NULL);
	t_line = malloc(sizeof(t_point_map) * *size_line);
	return (t_line);
}

t_point_map	*conversion_line_to_point(char *line, int y, t_size_map *size_map)
{
	char		**parse_line;
	int			size_line;
	int			x;
	t_point_map	*t_line;

	t_line = NULL;
	x = 0;
	t_line = ft_create_t_line(&parse_line, line, &size_line, size_map);
	if (t_line == NULL)
	{
		ft_free_tab(parse_line);
		return (NULL);
	}
	while (parse_line[x] != 0)
	{
		t_line[x] = create_point(parse_line[x], x, y);
		if (t_line[x++].x == -1)
		{
			ft_free_tab(parse_line);
			free(t_line);
			return (NULL);
		}
	}
	ft_free_tab(parse_line);
	return (t_line);
}
