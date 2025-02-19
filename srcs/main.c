/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:58:38 by pde-petr          #+#    #+#             */
/*   Updated: 2025/02/19 16:45:21 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/home/pde-petr/lib/mlx.h"
#include "fcntl.h"
#include "fdfheader.h"


// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int ft_fdf(t_point_map **maps, t_size_map size_for_all_lign)
// {
// 	void	*mlx; //display
// 	// void	*mlx_win; //window
// 	// t_data	img; //image
// 	// int x;
// 	// int y;

// 	// mlx = mlx_init(); //display init
// 	// mlx_win = mlx_new_window(mlx, 1920, 1080, "./fdf"); //window init
// 	// img.img = mlx_new_image(mlx, 1920, 1080); //image init
// 	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 	// 							&img.endian);
// 	// draw_map(mlx, mlx_win, &img, maps, size_for_all_lign);
//     // mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	y = 0;
// \
// 	// while (y < size_for_all_lign.ymax)
// 	// {
// 	// 	x = 0;
// 	// 	while (x < size_for_all_lign.xmax)
// 	// 	{
// 	// 		\
// 	// 		my_mlx_pixel_put(&img, x, y, maps[y][x].color);
// 	// 		x++;
// 	// 	}
// 	// 	y++;
// 	// }
// 	// mlx_put_image_to_window(mlx, mlx_win, img.img, 500, 500);
//     // mlx_loop(mlx);
// 	return 0;
// }

int	main(int argc, char **argv)
{
	t_point_map	**maps;
	int			fd;
	t_size_map	size_for_all_lign;
	int			y;
	int			x;

	y = 0;
	maps = NULL;
	
	size_for_all_lign = (t_size_map){.xmax = -1, .ymax = 0};
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
		
		// ft_fdf(maps, size_for_all_lign);




		while (y < size_for_all_lign.ymax)
		{
			x = 0;
			while (x < size_for_all_lign.xmax)
			{
				printf("%X ", maps[y][x].color);
				x++;
			}
			printf("\n");
			y++;
		}
		ft_free_all(size_for_all_lign.ymax, maps, NULL);
		return (0);
	}
}
