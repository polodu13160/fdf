/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:58:38 by pde-petr          #+#    #+#             */
/*   Updated: 2025/02/27 22:03:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/home/pde-petr/lib/mlx.h"
#include "fcntl.h"
#include "fdfheader.h"
#include <math.h>
#include "stdlib.h"
#define angle 0.523599 





int ft_fdf(t_point_map **maps, t_size_map size_for_all_lign)
{
    int x;
    int y;

    void *mlx;                                          // display
    void *mlx_win;                                      // window
    t_data img;                                         // image
    mlx = mlx_init();                                   // display init
    mlx_win = mlx_new_window(mlx, 1920, 1080, "./fdf"); // window init
    img.img = mlx_new_image(mlx, 4000, 4000);           // image init
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    y = 0;
    while (y++ < size_for_all_lign.ymax)
    {
        x = 0;
        while (x++ < size_for_all_lign.xmax)
            draw_image(maps, size_for_all_lign, x - 1, y - 1, &img);
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    
    mlx_loop(mlx);
    return 0;
}

void ft_trigo(t_point_map **maps, t_size_map *size_for_all_lign, int xmin, int ymin);

void ft_recurs_trigo(t_point_map **maps, t_size_map *size_for_all_lign)
{
	int y;
	int x;
	if (size_for_all_lign->newxmin < 0)
		size_for_all_lign->newxmin  = -size_for_all_lign->newxmin ;
	if (size_for_all_lign->newymin < 0)
		size_for_all_lign->newymin = -size_for_all_lign->newymin;
	
	// float zoom_x = (1920) / (size_for_all_lign->newxmax + size_for_all_lign->newxmin) ;
    // float zoom_y = (1080)/ (size_for_all_lign->newymax + size_for_all_lign->newymin)  ;
	// size_for_all_lign->zoom = fmin(zoom_x, zoom_y);
// size_for_all_lign->zoom = 3;

	
	
	
	ft_trigo(maps, size_for_all_lign, size_for_all_lign->newxmin, size_for_all_lign->newymin);
	
}

void ft_trigo(t_point_map **maps, t_size_map *size_for_all_lign, int xmin, int ymin)
{
	int y;
	int x;
	static int init = 0;
	
	y = -1;
	size_for_all_lign->zoom = 3;
	while (++y < size_for_all_lign->ymax)
	{
		x = -1;
		while (++x < size_for_all_lign->xmax)
		{
			maps[y][x].z.x = (maps[y][x].x * size_for_all_lign->zoom) * cos(angle) + (maps[y][x].y * size_for_all_lign->zoom) * cos(angle + 2) + (maps[y][x].z.z) * cos(angle - 2) + xmin;
			maps[y][x].z.y = (maps[y][x].x * size_for_all_lign->zoom) * sin(angle) + (maps[y][x].y * size_for_all_lign->zoom) * sin(angle + 2) + (maps[y][x].z.z) * sin(angle - 2) + ymin;
			if ((x == 0 && y == 0) || maps[y][x].z.x < size_for_all_lign->newxmin)
				size_for_all_lign->newxmin = maps[y][x].z.x;
			if ((x == 0 && y == 0) || maps[y][x].z.x > size_for_all_lign->newxmax)
				size_for_all_lign->newxmax = maps[y][x].z.x;
			if ((x == 0 && y == 0) || maps[y][x].z.y < size_for_all_lign->newymin)
				size_for_all_lign->newymin = maps[y][x].z.y;
			if ((x == 0 && y == 0) || maps[y][x].z.y > size_for_all_lign->newymax)
				size_for_all_lign->newymax = maps[y][x].z.y;
		}
	}
	if (init++ == 0)
		ft_recurs_trigo(maps, size_for_all_lign);
}

int	main(int argc, char **argv)
{
	t_point_map	**maps;
	int			fd;
	t_size_map	size_for_all_lign;

	maps = NULL;
    
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			perror("Erreur lors de l'ouverture du fichier");
			return (1);
		}
		if (ft_parsing(fd, &maps, &size_for_all_lign) == 1)
		{
			perror("Erreur lors du parsing");
			return (1);
		}
		ft_trigo(maps,&size_for_all_lign, 0, 0);
		ft_fdf(maps, size_for_all_lign);
		ft_free_all(size_for_all_lign.ymax, maps, NULL);
		return (0);
	}
}
