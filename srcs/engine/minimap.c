/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:49:29 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/19 19:11:47 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(mlx_image_t *image, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 30)
	{
		j = 0;
		while (j < 30)
		{
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	mini_map(t_data *data)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	x = 0;
	while (data->world.map[i])
	{
		j = 0;
		y = 0;
		while (data->world.map[i][j])
		{
			if (data->world.map[i][j] == '1')
				draw_square(data->world.minim, y, x, 0xFFFFFFFF);
			// else if (data->world.map[i][j] == '2')
			// 	draw_square(data->world.minim, x, y, 0x0000FF00);
			// else if (data->world.map[i][j] == '0')
			// 	draw_square(data->world.minim, x, y, 0x000000FF);
			else if (data->world.map[i][j] == 'N' || data->world.map[i][j] == 'S' ||
					data->world.map[i][j] == 'E' || data->world.map[i][j] == 'W')
				draw_square(data->pl.img, y, x, 0x00FFFFFF);
			j++;
			y += 30;
		}
		i++;
		x += 30;
	}
}

