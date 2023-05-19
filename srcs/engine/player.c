/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:45:52 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/19 18:46:27 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->world.map[i])
	{
		j = 0;
		while (data->world.map[i][j] && data->world.map[i][j] != '\n')
		{
			if (data->world.map[i][j] == 'N' || data->world.map[i][j] == 'S' ||
				data->world.map[i][j] == 'E' || data->world.map[i][j] == 'W')
			{
				data->pl.px = (j * 32);
				data->pl.py = (i * 32);
				data->pl.pa = 0.0;
				data->pl.pdx = cos(data->pl.pa) * 5;
				data->pl.pdy = sin(data->pl.pa) * 5;
				return ;
			}
			j++;
		}
		i++;
	}
}
