/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:50:42 by pde-petr          #+#    #+#             */
/*   Updated: 2025/02/27 19:29:24 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfheader.h"
#include <stdlib.h>


int	size_tab(char **split_point)
{
	int	i;

	i = 0;
	while (split_point[i])
		i++;
	return (i);
}
void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_all(int y, t_point_map **maps, t_stock_maps *lst)
{
	int	i;
	t_stock_maps *temp;
	temp = NULL;
	i = 0;
	if (maps != NULL)
	{
		while (i < y)
			free(maps[i++]);
		free(maps);
	}
	i = 0;
	if (lst != NULL)
	{
		while (lst)
		{
			temp = NULL;
			if (lst->next != NULL)
				temp = lst->next;
			free(lst->text);
			free(lst);
			if (temp == NULL)
				break; 
			lst = temp;
		}
	}
}

int ft_hexa_color(char *split_join)
{
	int i;
	i = 0;	
	int number_hexa;
	number_hexa = 0;
	if ((split_join[i] != '0') && (ft_tolower(split_join[i+1]) == 'x'))
		return 0xFFFFFF;
	i = 2;
	while (split_join[i])
	{
		if (split_join[i] >= '0' && split_join[i] <= '9')
			number_hexa = number_hexa * 16 + split_join[i] - '0';
		else if (ft_tolower(split_join[i]) >= 'a' && ft_tolower(split_join[i]) <= 'f')
			number_hexa = number_hexa * 16 + ft_tolower(split_join[i]) - 'a' + 10;
		else 
			return 0xFFFFFF;
		i++;
	}
	return number_hexa;
}

t_point_map	create_point(char *split_line, int x, int y)
{
	char **split_point;
	static int error_atoi = 0;
	t_point_map new_point;

	new_point = (t_point_map){.color = 0, .y = 0, .x = -1};
	split_point = ft_split(split_line, ',');
	if (split_point == NULL)
		new_point.x = -1;
	else
	{
		new_point.x = x;
		new_point.y = y;
		new_point.z.z = ft_atoi(split_point[0], &error_atoi);
		if (size_tab(split_point) == 2)
			new_point.color = ft_hexa_color(split_point[1]);
		else
			new_point.color = 0xFFFFFF;
	}
	if (error_atoi == -1)
		new_point.x = -1;
	ft_free_tab(split_point);
	return (new_point);
}


