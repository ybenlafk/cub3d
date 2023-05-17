/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:38:38 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/17 19:43:12 by aarbaoui         ###   ########.fr       */
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

// void raycast(t_data *data, float player_x, float player_y, float player_angle)
// {
//     const float ray_angle_step = FOV / NUM_RAYS;
//     const float start_angle = player_angle - FOV / 2 + (FOV - VIEW_ANGLE) / 2;
//     float ray_angle = start_angle;

//     // Create a new image for drawing walls
// 	mlx_delete_image(data->mlx, wall_image);
//     mlx_image_t *wall_image = mlx_new_image(data->mlx, 1, HEIGHT);
	
//     for (int i = 0; i < NUM_RAYS; ++i)
//     {
//         float ray_x = cos(ray_angle);
//         float ray_y = sin(ray_angle);

//         float delta_dist_x = fabs(1 / ray_x);
//         float delta_dist_y = fabs(1 / ray_y);

//         float side_dist_x, side_dist_y;
//         float perp_dist;

//         int map_x = (int)player_x;
//         int map_y = (int)player_y;

//         float step_x = (ray_x < 0) ? -1 : 1;
//         float step_y = (ray_y < 0) ? -1 : 1;

//         if (ray_x < 0)
//             side_dist_x = (player_x - map_x) * delta_dist_x;
//         else
//             side_dist_x = (map_x + 1.0 - player_x) * delta_dist_x;

//         if (ray_y < 0)
//             side_dist_y = (player_y - map_y) * delta_dist_y;
//         else
//             side_dist_y = (map_y + 1.0 - player_y) * delta_dist_y;

//         int hit = 0;
//         while (!hit)
//         {
//             if (side_dist_x < side_dist_y)
//             {
//                 side_dist_x += delta_dist_x;
//                 map_x += step_x;
//                 hit = data->world->map[map_y / 32][map_x / 32] == '1';
//                 perp_dist = (map_x - player_x + (1 - step_x) / 2) / ray_x;
//             }
//             else
//             {
//                 side_dist_y += delta_dist_y;
//                 map_y += step_y;
//                 hit = data->world->map[map_y / 32][map_x / 32] == '1';
//                 perp_dist = (map_y - player_y + (1 - step_y) / 2) / ray_y;
//             }
//         }

//         // Calculate the endpoint of the line
//         float line_end_x = player_x + ray_x * perp_dist;
//         float line_end_y = player_y + ray_y * perp_dist;

//         mlx_draw_line(data->p.line, player_x, player_y, line_end_x, line_end_y, 0xFF0000FF);

//         // Draw the wall on the wall image
//         int wall_height = HEIGHT / (perp_dist * cos(ray_angle - player_angle)) * WALL_SCALE;
//         int wall_top = HEIGHT / 2 - wall_height / 2;
//         mlx_draw_line(wall_image, 0, wall_top, 0, wall_top + wall_height, 0xFF0000FF);

//         ray_angle += ray_angle_step;

//         // Break the loop if we have covered the desired angle
//         if (ray_angle >= start_angle + VIEW_ANGLE)
//             break;
//     }

//     // Display the wall image
//     mlx_image_to_window(data->mlx, wall_image, WIDTH / 2, HEIGHT /2 );
// }



void raycast(t_data *data, float player_x, float player_y, float player_angle)
{
    const float ray_angle_step = FOV / NUM_RAYS;
    const float start_angle = player_angle - FOV / 2 + (FOV - VIEW_ANGLE) / 2;
    float ray_angle = start_angle;
    int walls[NUM_RAYS][2];
    mlx_image_t *wall_image = mlx_new_image(data->mlx, 1, HEIGHT);
    for (int i = 0; i < NUM_RAYS; ++i)
    {
        float ray_x = cos(ray_angle);
        float ray_y = sin(ray_angle);

        float delta_dist_x = fabs(1 / ray_x);
        float delta_dist_y = fabs(1 / ray_y);

        float side_dist_x, side_dist_y;
        float perp_dist;

        int map_x = (int)player_x;
        int map_y = (int)player_y;

        float step_x = (ray_x < 0) ? -1 : 1;
        float step_y = (ray_y < 0) ? -1 : 1;

        if (ray_x < 0)
            side_dist_x = (player_x - map_x) * delta_dist_x;
        else
            side_dist_x = (map_x + 1.0 - player_x) * delta_dist_x;

        if (ray_y < 0)
            side_dist_y = (player_y - map_y) * delta_dist_y;
        else
            side_dist_y = (map_y + 1.0 - player_y) * delta_dist_y;

        int hit = 0;
        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                hit = data->world->map[map_y / 32][map_x / 32] == '1';
                perp_dist = (map_x - player_x + (1 - step_x) / 2) / ray_x;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                hit = data->world->map[map_y / 32][map_x / 32] == '1';
                perp_dist = (map_y - player_y + (1 - step_y) / 2) / ray_y;
            }
        }

        // Calculate the endpoint of the line
        float line_end_x = player_x + ray_x * perp_dist;
        float line_end_y = player_y + ray_y * perp_dist;

        mlx_draw_line(data->p.line, player_x, player_y, line_end_x, line_end_y, 0xFF0000FF);
        int wall_height = HEIGHT / (perp_dist * cos(ray_angle - player_angle)) * WALL_SCALE;
        int wall_top = HEIGHT / 2 - wall_height / 2;
        int wall_bottom = wall_top + wall_height;

        // Draw the wall on the wall image
        mlx_draw_line(data->p.line, i, wall_top, i, wall_bottom, 0xFFFFFFFF);
        
        ray_angle += ray_angle_step;
        // Break the loop if we have covered the desired angle
        if (ray_angle >= start_angle + VIEW_ANGLE)
            break;
    }
}


static void ft_hook(void* param)
{
    (void)param;
    t_data *data = (t_data *)param;
    
    // Store the current position to check for collisions
    float new_px = data->p.px;
    float new_py = data->p.py;
	int cell_x;
	int cell_y;
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
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        new_px -= data->p.pdy;
        new_py += data->p.pdx;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        new_px += data->p.pdy;
        new_py -= data->p.pdx;
    }

    // Check for collisions with walls
    cell_x = (int)new_px  / 32;
    cell_y = (int)new_py / 32;

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
    mlx_draw_line(data->p.line, data->p.px , data->p.py, data->p.px + data->p.pdx * 16, data->p.py + data->p.pdy * 16, 0xFFFFFFF);
	 raycast(data, data->p.px, data->p.py, data->p.pa);
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
				mlx_draw_line(var->line, var->px + 8, var->py + 8, var->px + 8 + var->pdx * 8, var->py + 8 + var->pdy * 8, 0xFFFFFFF);
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
