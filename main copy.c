#include "/home/pde-petr/lib/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_mlx
{
	int		xy[2];
	void	*mlx;
	void	*win;
}			t_mlx;

int	my_key_func(int keycode, void *param)
{
	t_mlx *tab = (t_mlx *)param; // Correction : il faut caster param en t_mlx*
	if (keycode == 65362) // Flèche haut
	{
		if (tab->xy[1] > 0)
			tab->xy[1]--;
	}
	if (keycode == 65364) // Flèche bas
	{
		if (tab->xy[1] < 499)
			tab->xy[1]++;
	}
	if (keycode == 65361) // Flèche gauche
	{
		if (tab->xy[0] > 0)
			tab->xy[0]--;
	}
	if (keycode == 65363) // Flèche droite
	{
		if (tab->xy[0] < 499)
			tab->xy[0]++;
	}
	printf("key_event %d\n", keycode);
	printf("x %d y %d\n", tab->xy[0], tab->xy[1]);
	mlx_pixel_put(tab->mlx, tab->win, tab->xy[0], tab->xy[1], 0x00FFFFFF);
	return (0);
}

int	main(void)
{
	t_mlx test;
	test.mlx = mlx_init();
	if (!test.mlx)
	{
		fprintf(stderr, "Erreur : Impossible d'initialiser MLX\n");
		return (1);
	}

	test.xy[0] = 250; // Initialiser x au centre
	test.xy[1] = 250; // Initialiser y au centre
	test.win = mlx_new_window(test.mlx, 500, 500, "FDF");

	mlx_key_hook(test.win, my_key_func, &test); // On passe &test,
		car my_key_func attend un pointeur

	mlx_loop(test.mlx);
	return (0);
}


// void	put_pixel_image(t_pixel pixel, char *str, int color)
// {
// 	unsigned char r;
// 	unsigned char g;
// 	unsigned char b;
// 	int len;

// 	len = WIN_LEN; /* En réalité, il s'agit de la longueur de votre image. Ici,
// 		mon image et ma fenêtre font la même taille */

//
// 	/* in this part you'll see how i decompose a decimal color in a third part decimal color rgb(255,
// 		255, 255) */
// // 	/* Dans cette partie,
// 		voici comment je decompose une couleur decimal en une couleur décimale en trois partie rgb(255,
// 		255, 255) */
// 	r = (color >> 16) & 0xff;
// 	g = (color >> 8) & 0xff;
// 	b = color & 0xff;

// 	/* (pixel.x * 4) + (len * 4 * pixel.y) : cible le premier bit d'un pixel */
// 	str[(pixel.x * 4) + (len * 4 * pixel.y)] = b;
// 	str[(pixel.x * 4) + (len * 4 * pixel.y) + 1] = g;
// 	str[(pixel.x * 4) + (len * 4 * pixel.y) + 2] = r;
// 	str[(pixel.x * 4) + (len * 4 * pixel.y) + 3] = 0;
// }

// int main(void)
// {
//     // t_img img_str;
//     // void *mlx = mlx_init();
//     // int largeur = 1;
//     // int hauteur = 1;
//     // void *img = mlx_new_image(&mlx, largeur, hauteur);

//     // char *img_str = mlx_get_data_addr(img, 0, 0, 0);

//     // mlx_loop(mlx);
// 	parse_
//     return (0);
// }

