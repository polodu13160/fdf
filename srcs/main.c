/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paul <paul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:58:38 by pde-petr          #+#    #+#             */
/*   Updated: 2025/02/28 23:48:02 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdfheader.h"
#include "fcntl.h"







int	ft_fdf(t_point_map **maps, t_size_map size_map)
{
	int		x;
	int		y;
	t_vars	vars;

	vars = (t_vars){.maps = maps, .size_map = size_map, .mlx = NULL,
		.win = NULL, .img = (t_data){.img = NULL, .addr = NULL,
		.bits_per_pixel = 0, .line_length = 0, .endian = 0}};
	if (init_mlx(&vars) == 1)
		return (1);
	y = 0;
	while (y++ < size_map.ymax)
	{
		x = 0;
		while (x++ < size_map.xmax)
			draw_image(maps, size_map, x - 1, y - 1, &vars.img);
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	// mlx_key_hook(vars.win, press_esc, &vars);
	mlx_hook(vars.win, 2, (1L<<0), press_esc, &vars);
	mlx_hook(vars.win, 17, 0L, close_windows, &vars);
	mlx_loop(vars.mlx);
	return (0);
}


int	main(int argc, char **argv)
{
	t_point_map	**maps;
	int			fd;
	t_size_map	size_map;

	maps = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1 || ft_parsing(fd, &maps, &size_map) == 1)
		{
			if (fd == -1)
				perror("Erreur lors de l'ouverture du fichier");
			else
				perror("Erreur lors du parsing");
			return (1);
		}
		ft_trigo(maps, &size_map, 0, 0);
		ft_fdf(maps, size_map);
		return (0);
	}
}
