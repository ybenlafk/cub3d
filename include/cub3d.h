/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:34:22 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/16 15:57:34 by aarbaoui         ###   ########.fr       */
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
#define FOV 3.14159f  // Field of view in radians
#define NUM_RAYS 120  // Number of rays to cast
#define VIEW_ANGLE 1.0472f // view angle
#define WALL_SCALE 32
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
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
	int		i;
	int		j;
	int		l;
	int		x;
	int		y;
	char	*s;
	char	**str;
	void	*mlx;
	void	*win;
}			t_var;

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

#endif