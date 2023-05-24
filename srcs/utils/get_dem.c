/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:48:53 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/24 13:51:57 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calculate_map_dimensions(t_data* data)
{
	char **map = data->world.map;
	int i = 0;
	int j = 0;
	int max = 0;
	int count = 0;
	
	while (map[i])
	{
		j = 0;
		count = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			count++;
			j++;
		}
		if (count > max)
			max = count;
		i++;
	}
	data->world.map_width = max;
	data->world.map_height = i;
}
