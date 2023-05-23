/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:49:29 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/23 19:36:23 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_colorsize(int color_hex, int size)
{
	return (color_hex << 16 | size);
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
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	minimap(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->world.map[i])
	{
		j = 0;
		while (data->world.map[i][j])
		{
			if (data->world.map[i][j] == '1')
				draw_square(data->world.minim, j * 4, i * 4, 4, 0xFFF00FFF);
			else if (data->world.map[i][j] == '0')
				draw_square(data->world.minim, j * 4, i * 4, 4, 0xFF0000FF);
			else if (ft_strchr("NSEW", data->world.map[i][j]))
				draw_square(data->pl.img, j * 4, i * 4, 4, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}