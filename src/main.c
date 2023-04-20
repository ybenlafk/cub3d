/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:38:38 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/04/20 03:41:36 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t* m_image;
static mlx_image_t* p_image;


void	draw_square(mlx_image_t *image, int x, int y, int size, int color)
{
	int i;
	int j;

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

void	draw_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->world->map[i])
	{
		j = 0;
		while (data->world->map[i][j])
		{
			if (data->world->map[i][j] == '1')
				draw_square(m_image, j * 32, i * 32, 32, 0xFFFFFFFF);
			j++;
			if (data->world->map[i][j] == 'N')
				draw_square(p_image, j * 32, i * 32, 32, 0xFF0000FF);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2)
		return (1);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	init_parse(data, argv[1]);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	m_image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	p_image = mlx_new_image(data->mlx, 32, 32);
	draw_map(data);
	mlx_image_to_window(data->mlx, m_image, 0, 0);
	mlx_image_to_window(data->mlx, p_image, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
