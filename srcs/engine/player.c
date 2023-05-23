/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:45:52 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/23 19:42:42 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->world.map[i])
	{
		j = 0;
		while (data->world.map[i][j] && data->world.map[i][j] != '\n')
		{
			if (data->world.map[i][j] == 'N' || data->world.map[i][j] == 'S' ||
				data->world.map[i][j] == 'E' || data->world.map[i][j] == 'W')
			{
				data->pl.px = (j * 32) + 16;
				data->pl.py = (i * 32) + 16;
				if (data->world.map[i][j] == 'N')
					data->pl.pa = PI / 2;
				if (data->world.map[i][j] == 'S')
					data->pl.pa = (3 * PI) / 2;
				if (data->world.map[i][j] == 'E')
					data->pl.pa = 0 / 2 * PI;
				if (data->world.map[i][j] == 'W')
					data->pl.pa = PI;
				data->pl.pdx = cos(data->pl.pa) * 5;
				data->pl.pdy = sin(data->pl.pa) * 5;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	check_movment(t_data *data, float new_px, float new_py)
{
	int	cell_x;
	int	cell_y;
	int	new_cell_x;
	int	new_cell_y;
	int	new_cell_x_slide;
	int	new_cell_y_slide;

	cell_x = (int)(new_px / 32);
	cell_y = (int)(new_py / 32);
	new_cell_x = (int)((new_px + data->pl.pdx) / 32);
	new_cell_y = (int)((new_py + data->pl.pdy) / 32);
	if (data->world.map[cell_y][new_cell_x] == '1'
		&& data->world.map[new_cell_y][cell_x] == '1')
		return ;
	if (data->world.map[cell_y][new_cell_x] == '1')
		new_px = data->pl.px;
	if (data->world.map[new_cell_y][cell_x] == '1')
		new_py = data->pl.py;
	new_cell_x_slide = (int)((new_px + data->pl.pdx) / 32);
	new_cell_y_slide = (int)((new_py + data->pl.pdy) / 32);
	if (data->world.map[cell_y][new_cell_x_slide] == '1'
		|| data->world.map[new_cell_y_slide][cell_x] == '1')
		return ;
	data->pl.px = new_px;
	data->pl.py = new_py;
}
void	move_player(t_data *data, t_var *p)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		p->speed = 2;
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
