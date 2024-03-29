/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:16:54 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/25 09:21:24 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update(t_data *data)
{
	mlx_delete_image(data->mlx, data->world.walls);
	data->world.walls = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	raycast(data, data->pl.px, data->pl.py, data->pl.pa);
	mlx_image_to_window(data->mlx, data->world.walls, 0, 0);
}
void	ft_hook(void *param)
{
	t_data	*data;
	t_var	p;
	int		x;
	int		y;

	x = 0;
	y = 0;
	data = (t_data *)param;
	p.speed = 3;
	p.new_px = data->pl.px;
	p.new_py = data->pl.py;
	move_player(data, &p);
	check_movment(data, p.new_px, p.new_py);
	if (data->pl.pa > 2 * PI)
		data->pl.pa -= 2 * PI;
	if (data->pl.pa < 0)
		data->pl.pa += 2 * PI;
	update(data);
}

void	fill_png(unsigned int *list, mlx_texture_t *png)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (png->pixels[i] && j < png->width * png->height)
	{
		list[j] = get_rgba(png->pixels[i], png->pixels[i + 1], png->pixels[i
				+ 2], 255);
		i += 4;
		j++;
	}
}

int check_texture(t_data *data)
{
	if (!data->NO || !data->SO || !data->WE || !data->EA)
		return (1);
	if (data->NO->height != 64 || data->NO->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	if (data->SO->height != 64 || data->SO->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	if (data->WE->height != 64 || data->WE->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	if (data->EA->height != 64 || data->EA->width != 64)
		return (printf("Error\n🚨: Image error\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data *data;

	if (ac != 2)
		return (0);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx_set_setting(MLX_DECORATED, false);
	if (!data)
		return (1);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, 500, 500);
	init_parse(data, av[1]);
	data->NO = mlx_load_png(data->world.no);
	data->SO = mlx_load_png(data->world.so);
	data->WE = mlx_load_png(data->world.we);
	data->EA = mlx_load_png(data->world.ea);
	data->world.walls = mlx_new_image(data->mlx, WIDTH, HEIGHT);
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
	mlx_image_to_window(data->mlx, data->world.skybox, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	return (0);
}