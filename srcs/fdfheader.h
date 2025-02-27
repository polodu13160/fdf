/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfheader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:59:49 by pde-petr          #+#    #+#             */
/*   Updated: 2025/02/27 19:59:40 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDFHEADER_H
# define FDFHEADER_H

# include "libft_updated/libft.h"

#define HEXA "0123456789ABCDEF"

typedef struct s_draw_line
{
	int color;
    int steps;
	int x;
	int y;
    int dx, dy;
    float x_inc, y_inc;
    float x0, y0;
    int index;
}			t_draw_line;
typedef struct s_stock_maps
{
	char *text;
	struct s_stock_maps *next;
	
}			t_stock_maps;
typedef struct s_z
{
	int y;
	int x;
	int z;
}			t_z;
typedef struct s_point_map
{
	int	color;
	t_z		z;
	int		y;
	int		x;

}			t_point_map;
typedef struct s_size_map
{
	int		xmax;
	int		ymax;
	float	zoom;
	int 	height;
	int		length;
	int		newymax;
	int		newxmax;
	int		newymin;
	int 	newxmin;	
}			t_size_map;
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
t_point_map	*ft_create_t_lign(char ***parse_lign, char *line, int *size_lign,
				t_size_map *size_for_all_lign);
t_point_map	*ft_create_map_lign(char *line, int y,
				t_size_map *size_for_all_lign);
void verif_line_map(t_stock_maps **get_line, t_size_map *size_for_all_lign, int fd,t_stock_maps **start);
char		*ft_delete_lf(char *line);
int			ft_parsing(int fd, t_point_map ***maps,
				t_size_map *size_for_all_lign);
int			size_tab(char **split_point);
void		ft_free_tab(char **tab);
void	ft_free_all(int y, t_point_map **maps, t_stock_maps *lst);
t_point_map	create_point(char *split_line, int x, int y);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int draw_line(t_point_map **data, t_draw_line info_draw, t_data *img);
int draw_line_vertical(t_point_map **data, t_draw_line info_draw, t_data *img);
void draw_image(t_point_map **data, t_size_map size, int x, int y, t_data *img);
void ft_recurs_trigo(t_point_map **maps, t_size_map *size_for_all_lign);


#endif