/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:50:42 by pde-petr          #+#    #+#             */
/*   Updated: 2025/02/27 13:30:30 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "fdfheader.h"
#include <stdio.h>
#include <stdlib.h>

t_point_map	*ft_create_t_lign(char ***parse_lign, char *line, int *size_lign,
		t_size_map *size_for_all_lign)
{
	t_point_map	*t_lign;

	(*parse_lign) = ft_split(line, ' ');
	if (*parse_lign == NULL)
		return (NULL);
	*size_lign = size_tab(*parse_lign);
	if (size_for_all_lign->xmax == -1)
		size_for_all_lign->xmax = *size_lign;
	if (size_for_all_lign->xmax != *size_lign)
		return (NULL);
	t_lign = malloc(sizeof(t_point_map) * *size_lign);
	return (t_lign);
}

t_point_map	*ft_create_map_lign(char *line, int y,
		t_size_map *size_for_all_lign)
{
	char		**parse_lign;
	int			size_lign;
	int			x;
	t_point_map	*t_lign;

	t_lign = NULL;
	x = 0;
	t_lign = ft_create_t_lign(&parse_lign, line, &size_lign, size_for_all_lign);
	if (t_lign == NULL)
	{
		ft_free_tab(parse_lign);
		return (NULL);
	}
	while (parse_lign[x] != 0)
	{
		t_lign[x] = create_point(parse_lign[x], x, y);
		if (t_lign[x++].x == -1)
		{
			ft_free_tab(parse_lign);
			free(t_lign);
			return (NULL);
		}
	}
	ft_free_tab(parse_lign);
	return (t_lign);
}
void	ft_free_list(t_stock_maps *tab)
{
	t_stock_maps	*temp;

	while (tab)
	{
		temp = tab;
		tab = tab->next;
		free(temp->text);
		free(temp);
	}
}

void create_list(t_stock_maps **get_line, t_size_map *size, t_stock_maps **start, int fd)
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
			break;
		}
		else 
			*get_line = (*get_line)->next;
		size->ymax++;
	}
}

void	ft_size_y_map(t_size_map *size, int fd, t_stock_maps **get_line,
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

void	verif_line_map(t_stock_maps **get_line, t_size_map *size_for_all_lign,
		int fd, t_stock_maps **start)
{
	*size_for_all_lign = (t_size_map){.xmax = -1, .ymax = 0, .height = 0, .length = 0, \
	.newxmax = 0, .newxmin = 0, .newymax = 0, .zoom = 0};
	ft_size_y_map(size_for_all_lign, fd, get_line, start);
	close(fd);
	if ((*size_for_all_lign).ymax == 0)
		exit(1);
	*get_line = *start;
}

int ft_free_line(t_stock_maps *get_line)
{
	free(get_line->text);
	free(get_line);
}

int	ft_parsing(int fd, t_point_map ***maps, t_size_map *size_for_all_lign)
{
	int				y;
	t_stock_maps	*get_line;
	t_stock_maps	*start;

	start = NULL;
	get_line = NULL;
	verif_line_map(&get_line, size_for_all_lign, fd, &start);
	y = 0;
	*maps = malloc(sizeof(t_point_map *) * (*size_for_all_lign).ymax);
	if (*maps == NULL)
		exit(1);
	while (start != NULL)
	{
		start->text = ft_delete_lf(start->text);
		(*maps)[y] = ft_create_map_lign(start->text, y, size_for_all_lign);
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
