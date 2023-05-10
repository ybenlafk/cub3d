/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:38:38 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/10 16:02:57 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*m_image;
static mlx_image_t	*p_image;
static mlx_image_t  *l_image;
static float		px;
static float		py;
static float		pdx;
static float		pdy;
static float		pa;


void mlx_draw_line(mlx_image_t *image, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = x1 < x2 ? 1 : -1;
	sy = y1 < y2 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	if (x1 == x2 && y1 == y2)
		mlx_put_pixel(image, x1, y1, color);
	// if any is negative, dont draw
	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
		return ;
	while (1)
	{
		mlx_put_pixel(image, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	draw_rays_3d(t_data	*data)
{
	int		i;
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	distance;
	float	fov;
	float	fov_left;
	float	fov_right;
	float	fov_mid;
	(void)data;
	fov = 60 * (PI / 180);
	fov_left = fov / 2;
	fov_right = fov / 2;
	fov_mid = fov / 2;
	i = 0;
	while (i < WIDTH)
	{
		ray_angle = pa - fov_left + (i * (fov / WIDTH));
		ray_x = px;
		ray_y = py;
		distance = 0;
		while (distance < 16)
		{
			ray_x += cos(ray_angle) * 0.1;
			ray_y += sin(ray_angle) * 0.1;
			distance += 0.1;
			if (ray_x < 0 || ray_y < 0 || ray_x > WIDTH || ray_y > HEIGHT)
				break ;
			
		}
		mlx_draw_line(m_image, px, py, ray_x, ray_y, 0x00FF00);
		i++;
	}
}

void	key_loop(void *mlx)
{
	if (px < 0 || py < 0 || px > WIDTH || py > HEIGHT)
		px = 0;
	if (py < 0 || py > HEIGHT)
		py = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		px -= pdx;
		py -= pdy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		px += pdx;
		py += pdy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		px += pdy;
		py -= pdx;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		px -= pdy;
		py += pdx;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		pa -= 0.1;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		pa += 0.1;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	p_image->instances[0].x = px;
	p_image->instances[0].y = py;
	
	// draw a line from the middle of the player to 16 pixels in front of it
	mlx_delete_image(mlx, l_image);
	l_image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_draw_line(l_image, px + 8, py + 8, px + 8 + pdx * 8, py + 8 + pdy * 8, 0xFF0000FF);
	mlx_image_to_window(mlx, l_image, 0, 0);
}

void	draw_square(mlx_image_t *image, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(image, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->world->map[i])
	{
		j = 0;
		while (data->world->map[i][j])
		{
			if (data->world->map[i][j] == '1')
				draw_square(m_image, j * 32, i * 32, 30, 0xFFFFFFFF);
			// draw player
			if (data->world->map[i][j] == 'N' || data->world->map[i][j] == 'S'
				|| data->world->map[i][j] == 'E'
				|| data->world->map[i][j] == 'W')
			{
				draw_square(p_image, 0, 0, 16, 0xFF0000FF);
				px = j * 32;
				py = i * 32;
				pdx = cos(pa) * 5;
				pdy = sin(pa) * 5;
				// draw the line from the middle of the player to 8 pixels in front of it
				mlx_draw_line(l_image, px + 8, py + 8, px + 8 + pdx * 4, py + 8 + pdy * 4, 0xFF0000FF);
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (1);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	init_parse(data, argv[1]);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	m_image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	p_image = mlx_new_image(data->mlx, 32, 32);
	l_image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	draw_map(data);
	mlx_image_to_window(data->mlx, m_image, 0, 0);
	mlx_image_to_window(data->mlx, p_image, px, py);
	mlx_image_to_window(data->mlx, l_image, 0, 0);
	// for (int i = 0; i < 100; i++)
	// 	draw_rays_3d(data);
	mlx_loop_hook(data->mlx, key_loop, data->mlx);
	mlx_loop(data->mlx);
	return (0);
}
