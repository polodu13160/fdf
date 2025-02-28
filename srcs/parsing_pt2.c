/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:50:42 by pde-petr          #+#    #+#             */
/*   Updated: 2025/02/28 23:09:46 by paul             ###   ########.fr       */
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



int	ft_hexa_color(char *split_join)
{
	int	i;
	int	number_hexa;

	i = 0;
	number_hexa = 0;
	if ((split_join[i] != '0') && (ft_tolower(split_join[i + 1]) == 'x'))
		return (0xFFFFFF);
	i = 2;
	while (split_join[i])
	{
		if (split_join[i] >= '0' && split_join[i] <= '9')
			number_hexa = number_hexa * 16 + split_join[i] - '0';
		else if (ft_tolower(split_join[i]) >= 'a'
			&& ft_tolower(split_join[i]) <= 'f')
			number_hexa = number_hexa * 16 + ft_tolower(split_join[i]) - 'a'
				+ 10;
		else
			return (0xFFFFFF);
		i++;
	}
	return (number_hexa);
}

t_point_map	create_point(char *split_line, int x, int y)
{
	char		**split_point;
	static int	error_atoi = 0;
	t_point_map	new_point;

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
