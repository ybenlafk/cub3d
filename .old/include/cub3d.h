/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:34:22 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/19 17:10:27 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define PI 3.14159265358979323846
# define ERROR 0
# define SUCCESS 1
# define WIDTH 1440
# define HEIGHT 1080
#define FOV 1.0472    // Field of View (60 degrees in radians)
#define NUM_RAYS 1440 // Number of rays to cast
#define VIEW_ANGLE 1.0472 // Viewing angle (60 degrees in radians)
#define WALL_SCALE 30  // Wall scale factor

typedef struct param
{
	int		x0;
	int		x1;
	int		x2;
	int		x3;

	int		y0;
	int		y1;
	int		y2;
	int		y3;

	int 	size;
}			t_param;

typedef struct s_world
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor_c;
	char	*ceil_c;
	char	**map;
}			t_world;
//variables struct
typedef struct var
{
	mlx_image_t	*p;
	mlx_image_t	*floor;
	mlx_image_t	*line;
	mlx_image_t	*img;
	mlx_image_t *wall_image;
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	int			i;
	int			j;
	int			l;
	int			x;
	int			y;

	float 		speed;
	float 		new_px;
	float 		new_py;
	int 		cell_x;
	int 		cell_y;
	char		*s;
	char		**str;
	void		*mlx;
	void		*win;
	// raycasting variables.
	float 	ray_angle_step;
	float 	start_angle;
	float 	ray_angle;
	float 	ray_x;
	float 	ray_y;
	float 	delta_dist_x;
	float 	delta_dist_y;
	float 	side_dist_x;
	float 	side_dist_y;
	float 	perp_dist;
	int 	map_x;
	int 	map_y;
	float 	step_x;
	float 	step_y;
	int		hit; 
	float	line_end_x;
	float	line_end_y;
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
}				t_var;

typedef struct s_data
{
	void	*mlx;
	t_var	p;
	t_world	*world;
}			t_data;


// parse.c
void		init_parse(t_data *data, char *map_fi);
// utils
int			is_map(char *line);
void    	put_str(char *s, int fd);
void   		draw_map_init(t_var p, t_var *var, t_param *t);
void   		square_init(t_var p, t_param *t, int size);
void   		draw_player(t_data *data, t_var p, t_param *t, t_var *var);
void		draw_square(mlx_image_t *image, t_param t, int color);
void 		mlx_draw_line(mlx_image_t *image, t_param t, int color);
void		ft_init(t_var *p, t_param t);
void    	moves(t_data *data, t_var *p);
void    	angels(t_data *data);
int 		get_step(float x);

#endif