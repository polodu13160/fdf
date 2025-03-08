/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfheader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldepetrini <pauldepetrini@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:59:49 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/08 20:09:21 by pauldepetri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDFHEADER_H
# define FDFHEADER_H
# ifndef LENGTH
#  define LENGTH 500
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif
# define ANGLE 0.523599

# include "mlx.h"
# include "libft.h"

# define HEXA "0123456789ABCDEF"

typedef struct s_z
{
	int					y;
	int					x;
	int					z;
}						t_z;
typedef struct s_point_map
{
	int					color;
	t_z					z;
	int					y;
	int					x;

}						t_point_map;
typedef struct s_data
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_data;
typedef struct s_size_map
{
	int					xmax;
	int					ymax;
	float				zoom;
	int					newymax;
	int					newxmax;
	int					newymin;
	int					newxmin;
}						t_size_map;
typedef struct s_vars
{
	void				*mlx;
	void				*win;
	struct s_point_map	**maps;
	struct s_size_map	size_map;
	struct s_data		img;
}						t_vars;
typedef struct s_draw_line
{
	int			color;
	int			steps;
	int			x;
	int			y;
	int			dx;
	int			dy;
	float		x_inc;
	float		y_inc;
	float		x0;
	float		y0;
	int			index;
}						t_draw_line;
typedef struct s_stock_maps
{
	char				*text;
	struct s_stock_maps	*next;

}						t_stock_maps;

void					free_mlx(t_vars *vars, int error);
void					ft_free_tab(char **tab);
void					ft_free_line(t_stock_maps *get_line);
void					ft_free_all(int y, t_point_map **maps,
							t_stock_maps *lst);
void					ft_free_list(t_stock_maps *tab);
char					*ft_delete_lf(char *line);
void					read_line(t_stock_maps **get_line, t_size_map *size_map,
							int fd, t_stock_maps **start);
int						ft_parsing(int fd, t_point_map ***maps,
							t_size_map *size_map);
int						size_tab(char **split_point);
int						ft_hexa_color(char *split_join);
t_point_map				create_point(char *split_line, int x, int y);
void					create_list(t_stock_maps **get_line, t_size_map *size,
							t_stock_maps **start, int fd);
void					create_tab_line(t_size_map *size, int fd,
							t_stock_maps **get_line, t_stock_maps **start);
t_point_map				*ft_create_t_line(char ***parse_line, char *line,
							int *size_line, t_size_map *size_map);
t_point_map				*conversion_line_to_point(char *line, int y,
							t_size_map *size_map);
void					ft_trigo(t_point_map **maps, t_size_map *size_map,
							int xmin, int ymin);
void					ft_recurs_trigo(t_point_map **maps,
							t_size_map *size_map);
void					redefine_small_and_big_xy(t_point_map **maps,
							t_size_map *size_map, int x, int y);
void					ft_trigo(t_point_map **maps, t_size_map *size_map,
							int xmin, int ymin);
int						init_mlx(t_vars *vars);
int						press_esc(int keycode, t_vars *vars);
int						close_windows(t_vars *vars);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
int						draw_line(t_point_map **data, t_draw_line info_draw,
							t_data *img);
int						draw_line_vertical(t_point_map **data,
							t_draw_line info_draw, t_data *img);
void					draw_image(t_vars *vars, int x, int y, t_data *img);

#endif