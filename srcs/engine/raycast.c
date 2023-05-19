/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:59:07 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/19 20:54:48 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_data *data, float player_x, float player_y,
		float player_angle)
{
	t_line		t;
	t_engine	p;
	int			wall_height;
	int			wall_top;
	int			wall_bottom;
	int			distance_shade;
	int			color;

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
				p.hit = data->world.map[p.map_y / 32][p.map_x / 32] == '1';
				p.perp_dist = (p.map_x - player_x + (1 - p.step_x) / 2)
					/ p.ray_x;
			}
			else
			{
				p.side_dist_y += p.delta_dist_y;
				p.map_y += p.step_y;
				p.hit = data->world.map[p.map_y / 32][p.map_x / 32] == '1';
				p.perp_dist = (p.map_y - player_y + (1 - p.step_y) / 2)
					/ p.ray_y;
			}
		}
		p.line_end_x = player_x + p.ray_x * p.perp_dist;
		p.line_end_y = player_y + p.ray_y * p.perp_dist;
		wall_height = HEIGHT / (p.perp_dist * cos(p.ray_angle - player_angle))
			* WALL_SCALE;
		wall_top = HEIGHT / 2 - wall_height / 2;
		wall_top = wall_top < 0 ? 0 : wall_top;
		wall_bottom = HEIGHT / 2 + wall_height / 2;
		wall_bottom = wall_bottom > HEIGHT ? HEIGHT : wall_bottom;
		t.x0 = p.i;
		t.y0 = wall_top;
		t.x1 = p.i;
		t.y1 = wall_bottom;
		distance_shade = (int)(255 - (p.perp_dist / MAX_RENDER_DISTANCE) * 255);
		distance_shade = distance_shade <= 0 ? 0 : distance_shade; 
		color = get_rgba(distance_shade, distance_shade, distance_shade,
				255);
		mlx_draw_line(data->world.walls, t, color);
		p.ray_angle += p.ray_angle_step;
		if (p.ray_angle >= p.start_angle + VIEW_ANGLE)
			break ;
		p.i++;
	}
}