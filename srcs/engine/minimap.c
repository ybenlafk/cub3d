/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:49:29 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/24 14:01:40 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// get player position
// draw space around player position from the double array data->world.map
// draw player position
void minimap(t_data* data)
{
	int px = data->pl.px / 32;
	int py = data->pl.py / 32;
	char** map = data->world.map;
	int minimap_size = 5; // Adjust the size of each minimap cell as needed
	int minimap_width = 40; // Adjust the width of the minimap as needed
	int minimap_height = 40; // Adjust the height of the minimap as needed
	int start_x = px - (minimap_width / 2);
	int start_y = py - (minimap_height / 2);
	int end_x = start_x + minimap_width;
	int end_y = start_y + minimap_height;
	int i, j;
	int x = 0;
	int y = 0;

	for (i = start_y; i < end_y; i++)
	{
		for (j = start_x; j < end_x; j++)
		{
			if (i >= 0 && j >= 0 && i < data->world.map_height && j < data->world.map_width)
			{
				if (map[i][j] == '1')
					draw_square(data->world.minim, x * minimap_size, y * minimap_size, minimap_size, 0xFFFFFFFF);
				else if (map[i][j] == 'N')
					draw_square(data->world.minim, x * minimap_size, y * minimap_size, minimap_size, 0xFFF00FFF);
				else
					draw_square(data->world.minim, x * minimap_size, y * minimap_size, minimap_size, 0x00000000);
			}
			x++;
		}
		x = 0;
		y++;
	}
}
