/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:16:54 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/19 19:12:45 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(void* param)
{
	t_data *data;
    t_var p;

    data = (t_data *)param;
    p.speed = 2;
    p.new_px = data->pl.px;
    p.new_py = data->pl.py;
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
        p.speed = 1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        exit(1);
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        p.new_px -= data->pl.pdx / p.speed;
        p.new_py -= data->pl.pdy / p.speed;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        p.new_px += data->pl.pdx / p.speed;
        p.new_py += data->pl.pdy / p.speed;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        p.new_px -= data->pl.pdy / p.speed;
        p.new_py += data->pl.pdx / p.speed;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        p.new_px += data->pl.pdy / p.speed;
        p.new_py -= data->pl.pdx / p.speed;
    }
    p.cell_x = (int)p.new_px / 32;
    p.cell_y = (int)p.new_py / 32;
    if (p.new_px >= 0 && p.new_px < WIDTH && p.new_py >= 0 && p.new_py < HEIGHT)
    {
        if (data->world.map[p.cell_y][p.cell_x] != '1')
        {
            data->pl.px = p.new_px;
            data->pl.py = p.new_py;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
    {
        data->pl.pa -= 0.05;
        data->pl.pdx = cos(data->pl.pa) * 5;
        data->pl.pdy = sin(data->pl.pa) * 5;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
    {
        data->pl.pa += 0.05;
        data->pl.pdx = cos(data->pl.pa) * 5;
        data->pl.pdy = sin(data->pl.pa) * 5;
    }
    data->pl.img->instances[0].x = data->pl.px;
    data->pl.img->instances[0].y = data->pl.py;

    mlx_delete_image(data->mlx, data->world.walls);
    data->world.walls = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	raycast(data, data->pl.px, data->pl.py, data->pl.pa);
    mlx_image_to_window(data->mlx, data->world.walls, 0, 0);
}

int main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (0);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!data)
		return (1);
	init_parse(data, av[1]);
	init_player(data);
	data->world.walls = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->world.minim = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->pl.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    mini_map(data);
    mlx_image_to_window(data->mlx, data->world.minim, 0, 0);
    mlx_image_to_window(data->mlx, data->pl.img, data->pl.px, data->pl.py);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	return (0);
}