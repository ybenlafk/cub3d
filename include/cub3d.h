/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:34:22 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/21 21:34:42 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# define PI 3.14159265358979323846
# define ERROR 0
# define SUCCESS 1
# define WIDTH 1440
# define HEIGHT 1080
# define FOV 1.0472        // Field of View (60 degrees in radians)
# define NUM_RAYS 1440     // Number of rays to cast
# define VIEW_ANGLE 1.0472 // Viewing angle (60 degrees in radians)
# define WALL_SCALE 30     // Wall scale factor
# define MAX_RENDER_DISTANCE 1000
# define MAXWIDTH 64
# define MAXHEIGHT 64

typedef struct s_line
{
	int			x0;
	int			x1;
	int			x2;
	int			x3;

	int			y0;
	int			y1;
	int			y2;
	int			y3;

	int			size;
}				t_line;

typedef struct s_var
{
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

	float		speed;
	float		new_px;
	float		new_py;
	int			cell_x;
	int			cell_y;
}				t_var;

typedef struct s_player
{
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
	mlx_image_t	*img;
}				t_player;

typedef struct s_engine
{
	float		ray_angle_step;
	float		start_angle;
	float		ray_angle;
	float		ray_x;
	float		ray_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		side_dist_x;
	float		side_dist_y;
	float		perp_dist;
	int			map_x;
	int			map_y;
	float		step_x;
	float		step_y;
	int			hit;
	float		line_end_x;
	float		line_end_y;
	int			wall_height;
	int			wall_top;
	int			wall_bottom;
	int			i;
}				t_engine;

typedef struct s_world
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*floor_c;
	char		*ceil_c;
	int			width;
	int			height;
	mlx_image_t	*walls;
	mlx_image_t	*minim;
	mlx_image_t	*skybox;
	char		**map;
}				t_world;

typedef struct s_data
{
	void		*mlx;
	t_engine	eng;
	t_player	pl;
	t_world		world;
	t_var		vr;
}				t_data;
//engine
void			raycast(t_data *data, float player_x, float player_y,
					float player_angle);
void			init_player(t_data *data);
void			minimap(t_data *data);
void			skybox(t_data *data);
// parsing
void			init_parse(t_data *data, char *map_fi);
// utils
int				is_map(char *line);
int				get_step(float x);
void			mlx_draw_line(mlx_image_t *image, t_line t, int color);
int				get_rgba(int r, int g, int b, int a);
int get_rgb(int r, int g, int b);
#endif