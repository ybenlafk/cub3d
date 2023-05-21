/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:16:54 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/21 21:44:48 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_movment(t_data *data, float new_px, float new_py)
{
	int	cell_x;
	int	cell_y;

	cell_x = (int)new_px / 32;
	cell_y = (int)new_py / 32;
	if (data->world.map[cell_y][cell_x] != '1')
	{
		data->pl.px = new_px;
		data->pl.py = new_py;
	}
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

	data = (t_data *)param;
	p.speed = 2;
	p.new_px = data->pl.px;
	p.new_py = data->pl.py;
	move_player(data, &p);
	check_movment(data, p.new_px, p.new_py);
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

int	main(int ac, char **av)
{
	t_data *data;
	mlx_texture_t *texture;
	
	if (ac != 2)
		return (0);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!data)
		return (1);
	init_parse(data, av[1]);
	// data->world.skybox = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	texture = mlx_load_png("./assets/textures/rickroll.png");
	int i = 0;
	int j = 0;
	mlx_image_t *img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	int colors[texture->width * texture->height];
	while (texture->pixels[i] && j < texture->width * texture->height)
	{
		colors[j] = get_rgba(texture->pixels[i], texture->pixels[i + 1], texture->pixels[i + 2], texture->pixels[i + 3]);
		i += 4;
		j++;
	}
	j= 0;
	while (j < texture->width * texture->height)
	{
		mlx_put_pixel(img, j % texture->width, j / texture->height, colors[j]);
		j++;
	}
	// while (colors[i] != 0)
	// {

	// 	printf("colors[%d] = %d\n", i, colors[i]);
	// 	i++;
	// }
	// while (texture->pixels[j * 64 * 4])
	// {
	// 	// // mlx_put_pixel(img, i , get_rgba(texture->pixels[i], texture->pixels[i + 1], texture->pixels[i + 2], texture->pixels[i + 3]));
	// 	// mlx_put_pixel(img, i , j , get_rgba(texture->pixels[i], texture->pixels[i + 1], texture->pixels[i + 2], texture->pixels[i + 3]));
	// 	// i += 4;
	// 	// j++;
	// 	i = 0;
	// 	while (i <= 64 * 4)
	// 	{
	// 		mlx_put_pixel(img, i , j , get_rgba(texture->pixels[i], texture->pixels[i + 1], texture->pixels[i + 2], texture->pixels[i + 3]));
	// 		i += 4;
	// 	}
	// 	j++;
	// }
	// mlx_image_to_window(dat a->mlx, img, 0, 0);
	// data->world.minim = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// data->pl.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// skybox(data);
	// minimap(data);
	// init_player(data);
	// data->world.walls = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(data->mlx, data->world.skybox, 0, 0);
	// // mlx_image_to_window(data->mlx, data->world.minim, 0, 0);
	// mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_image_to_window(data->mlx, img, 0, 0);

	mlx_loop(data->mlx);
	return (0);
}