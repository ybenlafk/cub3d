/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:38:38 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/23 14:37:51 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void mlx_draw_line(mlx_image_t *image, t_param t, int color)
{
	t_var p;

	ft_init(&p, t);
	if (t.x0 == t.x1 && t.y0 == t.y1)
		mlx_put_pixel(image, t.x0, t.y0, color);
	if (t.x0 < 0 || t.y0 < 0 || t.x1 < 0 || t.y1 < 0)
		return ;
	while (1)
	{
		mlx_put_pixel(image, t.x0, t.y0, color);
		if (t.x0 == t.x1 && t.y0 == t.y1)
			break ;
		p.e2 = p.err;
		if (p.e2 > -p.dx)
		{
			p.err -= p.dy;
			t.x0 += p.sx;
		}
		if (p.e2 < p.dy)
		{
			p.err += p.dx;
			t.y0 += p.sy;
		}
	}
}

void raycast(t_data *data, float player_x, float player_y, float player_angle)
{
    t_param t;
    t_var   p;

    p.ray_angle_step = FOV / NUM_RAYS;
    p.start_angle = player_angle - FOV / 2 + (FOV - VIEW_ANGLE) / 2;
    p.ray_angle = p.start_angle;
    p.i = 0;
    while (p.i < NUM_RAYS)
    {
        p.ray_x = cos(p.ray_angle);
        p.ray_y = sin(p.ray_angle);
        p.delta_dist_x = fabs(1 / p.ray_x);
        p.delta_dist_y = fabs(1 / p.ray_y);
        p.map_x = (int)player_x;
        p.map_y = (int)player_y;
        p.step_x = get_step(p.ray_x);
        p.step_y = get_step(p.ray_y);

        if (p.ray_x < 0)
            p.side_dist_x = (player_x - p.map_x) * p.delta_dist_x;
        else
            p.side_dist_x = (p.map_x + 1.0 - player_x) * p.delta_dist_x;

        if (p.ray_y < 0)
            p.side_dist_y = (player_y - p.map_y) * p.delta_dist_y;
        else
            p.side_dist_y = (p.map_y + 1.0 - player_y) * p.delta_dist_y;

        p.hit = 0;
        while (!p.hit)
        {
            if (p.side_dist_x < p.side_dist_y)
            {
                p.side_dist_x += p.delta_dist_x;
                p.map_x += p.step_x;
                p.hit = data->world->map[p.map_y / 32][p.map_x / 32] == '1';
                p.perp_dist = (p.map_x - player_x + (1 - p.step_x) / 2) / p.ray_x;
            }
            else
            {
                p.side_dist_y += p.delta_dist_y;
                p.map_y += p.step_y;
                p.hit = data->world->map[p.map_y / 32][p.map_x / 32] == '1';
                p.perp_dist = (p.map_y - player_y + (1 - p.step_y) / 2) / p.ray_y;
            }
        }

        p.line_end_x = player_x + p.ray_x * p.perp_dist;
        p.line_end_y = player_y + p.ray_y * p.perp_dist;

        int wall_height = HEIGHT / (p.perp_dist * cos(p.ray_angle - player_angle)) * WALL_SCALE;
        int wall_top = HEIGHT / 2 - wall_height / 2;
        wall_top = wall_top < 0 ? 0 : wall_top;
        int wall_bottom = HEIGHT / 2 + wall_height / 2;
        wall_bottom = wall_bottom > HEIGHT ? HEIGHT : wall_bottom;

        t.x0 = p.i;
        t.y0 = wall_top;
        t.x1 = p.i;
        t.y1 = wall_bottom;
        mlx_draw_line(data->p.line, t, 0xFFFFFFFF);
        
        p.ray_angle += p.ray_angle_step;
        if (p.ray_angle >= p.start_angle + VIEW_ANGLE)
            break;
        p.i++;
    }
}


static void ft_hook(void* param)
{
    t_data *data;
    t_var p;

    data = (t_data *)param;
    p.speed = 4;
    p.new_px = data->pl.px;
    p.new_py = data->pl.py;
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
        p->speed = 2;
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
    p.cell_x = (int)p.new_px  / 32;
    p.cell_y = (int)p.new_py / 32;
    if (p.new_px >= 0 && p.new_px < WIDTH && p.new_py >= 0 && p.new_py < HEIGHT)
    {
        if (data->world->map[p.cell_y][p.cell_x] != '1')
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
    mlx_delete_image(data->mlx, data->world.walls);
    data->world.walls = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	raycast(data, data->pl.px, data->pl.py, data->pl.pa);
    mlx_image_to_window(data->mlx, data->world.walls, 0, 0);
}

void	draw_map(t_data *data, t_var *var)
{
	t_var p;
    t_param t;

	p.i = 0;
	while (data->world->map[p.i])
	{
		p.j = 0;
		while (data->world->map[p.i][p.j])
		{
			if (data->world->map[p.i][p.j] == '1')
            {
                square_init(p, &t, 30);
				draw_square(var->img, t, 0xFFFFFFFF);
            }
			draw_player(data, p, &t, var);
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
	p.wall_image = mlx_new_image(data->mlx, WIDTH, HEIGHT);

	draw_map(data, &p);
	mlx_image_to_window(data->mlx, p.img, 0, 0);
	mlx_image_to_window(data->mlx, p.line, 0, 0);
	mlx_image_to_window(data->mlx, p.p, p.px, p.py);
	data->p = p;
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
