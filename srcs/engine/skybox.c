/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:18:26 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/24 14:29:48 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	all_int(char **av)
{
	int	i;
	int	j;
	char *s;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '-')
			j++;
		s = ft_strtrim(av[i], " \n\t\v\f\r");
		if (!s)
			return (1);
		while (s[j])
			if (!is_digit(s[j++]))
				return (free(s), 1);
		i++;
		free(s);
	}
	return (0);
}

void	skybox(t_data *data)
{
	char **colors[2];
	int i;
	int j;

	i = 0;
	j = 0;
	colors[0] = ft_split(data->world.ceil_c, ',');
	colors[1] = ft_split(data->world.floor_c, ',');
	if (!colors[0] || !colors[1])
		ft_error("Error\n🚨: Invalid colors\n");
	if (all_int(colors[0]) || all_int(colors[1]))
	{
		free_all(colors[0]);
		free_all(colors[1]);
		ft_error("Error\n🚨: Invalid colors\n");
	}
	while (i <= HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(data->world.skybox, j, i,
					get_rgba(ft_atoi(colors[0][0]), ft_atoi(colors[0][1]),
						ft_atoi(colors[0][2]), 255));
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
			mlx_put_pixel(data->world.skybox, j, i,
					get_rgba(ft_atoi(colors[1][0]), ft_atoi(colors[1][1]),
						ft_atoi(colors[1][2]), 255));
			j++;
		}
		i++;
	}
	free_all(colors[0]);
	free_all(colors[1]);
}