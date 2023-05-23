/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:45:52 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/23 15:16:46 by aarbaoui         ###   ########.fr       */
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
