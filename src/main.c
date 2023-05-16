/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:38:38 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/16 15:10:16 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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


static void ft_hook(void* param)
{
    (void)param;
    t_data *data = (t_data *)param;
    
    // Store the current position to check for collisions
    float new_px = data->p.px;
    float new_py = data->p.py;

    // Update the position based on keyboard input
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        new_px -= data->p.pdx;
        new_py -= data->p.pdy;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        new_px += data->p.pdx;
        new_py += data->p.pdy;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        new_px -= data->p.pdy;
        new_py += data->p.pdx;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        new_px += data->p.pdy;
        new_py -= data->p.pdx;
    }

    // Check for collisions with walls
    int cell_x = (int)new_px / 32;
    int cell_y = (int)new_py / 32;

    if (new_px >= 0 && new_px < WIDTH && new_py >= 0 && new_py < HEIGHT)
    {
        if (data->world->map[cell_y][cell_x] != '1')
        {
            // Update the position if there is no collision
            data->p.px = new_px;
            data->p.py = new_py;
        }
    }
    
    // Update player direction
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
    {
        data->p.pa -= 0.1;
        data->p.pdx = cos(data->p.pa) * 5;
        data->p.pdy = sin(data->p.pa) * 5;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
    {
        data->p.pa += 0.1;
        data->p.pdx = cos(data->p.pa) * 5;
        data->p.pdy = sin(data->p.pa) * 5;
    }

    // Update the position of the player instance
    data->p.p->instances[0].x = data->p.px;
    data->p.p->instances[0].y = data->p.py;

    // Draw a line from the middle of the player to 16 pixels in front of it
    mlx_delete_image(data->mlx, data->p.line);
    data->p.line = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    mlx_draw_line(data->p.line, data->p.px + 8, data->p.py + 8, data->p.px + 8 + data->p.pdx * 8, data->p.py + 8 + data->p.pdy * 8, 0xFF0000FF);
    mlx_image_to_window(data->mlx, data->p.line, 0, 0);
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

void	draw_map(t_data *data, t_var *var)
{
	t_var p;
	
	p.i = 0;
	while (data->world->map[p.i])
	{
		p.j = 0;
		while (data->world->map[p.i][p.j])
		{
			if (data->world->map[p.i][p.j] == '1')
				draw_square(var->img, p.j * 32, p.i * 32, 30, 0xFFFFFFFF);
			if (data->world->map[p.i][p.j] == 'N' || data->world->map[p.i][p.j] == 'S'
				|| data->world->map[p.i][p.j] == 'E'
				|| data->world->map[p.i][p.j] == 'W')
			{
				draw_square(var->p, 0, 0, 16, 0xFF0000FF);
				var->px = p.j * 32;
				var->py = p.i * 32;
				var->pdx = cos(var->pa) * 5;
				var->pdy = sin(var->pa) * 5;
				mlx_draw_line(var->line, var->px + 8, var->py + 8, var->px + 8 + var->pdx * 8, var->py + 8 + var->pdy * 8, 0xFF0000FF);
			}
			p.j++;
		}
		p.i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_var	p;
	
	p.pa = 0;
	if (ac != 2)
		return (1);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	init_parse(data, av[1]);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!data->mlx)
		return (put_str("mlx error\n", 2), exit(0), 0);
	p.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	p.p = mlx_new_image(data->mlx, 32, 32);
	p.line = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	draw_map(data, &p);
	mlx_image_to_window(data->mlx, p.img, 0, 0);
	mlx_image_to_window(data->mlx, p.line, 0, 0);
	mlx_image_to_window(data->mlx, p.p, p.px, p.py);
	data->p = p;
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
