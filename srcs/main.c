/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:16:54 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/23 18:16:20 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_movment(t_data *data, float new_px, float new_py)
{
    int cell_x = (int)(new_px / 32);
    int cell_y = (int)(new_py / 32);

	int new_cell_x = (int)((new_px + data->pl.pdx) / 32);
	int new_cell_y = (int)((new_py + data->pl.pdy) / 32);
    if (data->world.map[cell_y][new_cell_x] == '1'
		|| data->world.map[new_cell_y][cell_x] == '1')
        return;
    data->pl.px = new_px;
    data->pl.py = new_py;
}

void	move_player(t_data *data, t_var *p)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		p->speed = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		p->new_px -= data->pl.pdx / p->speed;
		p->new_py -= data->pl.pdy / p->speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		p->new_px += data->pl.pdx / p->speed;
		p->new_py += data->pl.pdy / p->speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		p->new_px -= data->pl.pdy / p->speed;
		p->new_py += data->pl.pdx / p->speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		p->new_px += data->pl.pdy / p->speed;
		p->new_py -= data->pl.pdx / p->speed;
	}
}

void	ft_hook(void *param)
{
	t_data	*data;
	t_var	p;
	int		mx;
	int		my;
	int		x = 0;
	int		y = 0;
	
	data = (t_data *)param;
	p.speed = 3;
	p.new_px = data->pl.px;
	p.new_py = data->pl.py;
	move_player(data, &p);
	check_movment(data, p.new_px, p.new_py);
	mlx_get_mouse_pos(data->mlx, &mx, &my);
	data->pl.pa += (mx - 500) / 500.0 * SENSE;
	data->pl.pdx = cos(data->pl.pa) * 5;
	data->pl.pdy = sin(data->pl.pa) * 5;
	mlx_set_mouse_pos(data->mlx, 500, 500);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->pl.pa -= 0.04;
		data->pl.pdx = cos(data->pl.pa) * 5;
		data->pl.pdy = sin(data->pl.pa) * 5;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->pl.pa += 0.04;
		data->pl.pdx = cos(data->pl.pa) * 5;
		data->pl.pdy = sin(data->pl.pa) * 5;
	}
	mlx_delete_image(data->mlx, data->world.walls);
	data->world.walls = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	raycast(data, data->pl.px, data->pl.py, data->pl.pa);
	mlx_image_to_window(data->mlx, data->world.walls, 0, 0);
}

void	fill_png(unsigned int *list, mlx_texture_t *png)
{
	unsigned int i = 0;
	unsigned int j = 0;
	while (png->pixels[i] && j <  png->width *  png->height)
	{
		list[j] = get_rgba(png->pixels[i], png->pixels[i + 1], png->pixels[i + 2], 255);
		i += 4;
		j++;
	}
}


int	main(int ac, char **av)
{
	t_data *data;
	if (ac != 2)
		return (0);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!data)
		return (1);
	init_parse(data, av[1]);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	data->NO = mlx_load_png("./assets/textures/STARG3_64.png");
	data->EA = mlx_load_png("./assets/textures/STARG2_64.png");
	data->SO = mlx_load_png("./assets/textures/STARG3_64.png");
	data->WE = mlx_load_png("./assets/textures/STARG2_64.png");
	if (!data->NO || !data->SO || !data->WE || !data->EA)
		exit(1);
	fill_png(data->tex_NO, data->NO);
	fill_png(data->tex_EA, data->EA);
	fill_png(data->tex_SO, data->SO);
	fill_png(data->tex_WE, data->WE);
	data->world.skybox = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->pl.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	skybox(data);
	init_player(data);
	data->world.walls = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->world.skybox, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	return (0);
}