/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:18:26 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/19 20:30:12 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_skybox(t_data *data)
{
	char **colors[2];
	int i;
	int j;

	i = 0;
	j = 0;
	colors[0] = ft_split(data->world.ceil_c, ',');
	colors[1] = ft_split(data->world.floor_c, ',');
	while (i <= HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(data->world.skybox, j, i, get_rgba(ft_atoi(colors[0][0]), ft_atoi(colors[0][1]), ft_atoi(colors[0][2]), 255));
			j++;
		}
		i++;
	}
	i = HEIGHT / 2;
	j = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(data->world.skybox, j, i, get_rgba(ft_atoi(colors[1][0]), ft_atoi(colors[1][1]), ft_atoi(colors[1][2]), 255));
			j++;
		}
		i++;
	}
}