/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:07:39 by paul              #+#    #+#             */
/*   Updated: 2025/03/04 15:44:45 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfheader.h"
#include <stdlib.h>

void	free_mlx(t_vars *vars, int error)
{
	if (error == 1)
		mlx_destroy_display(vars->mlx);
	else if (error == 2)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
	}
	else if (error >= 3)
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
	}
	free(vars->mlx);
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

void	ft_free_line(t_stock_maps *get_line)
{
	free(get_line->text);
	free(get_line);
}

void	ft_free_all(int y, t_point_map **maps, t_stock_maps *lst)
{
	int				i;
	t_stock_maps	*temp;

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
			ft_free_line(lst);
			if (temp == NULL)
				break ;
			lst = temp;
		}
	}
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
