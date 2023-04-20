/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:38:38 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/04/20 00:34:11 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2)
		return (1);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	init_parse(data, argv[1]);
	int i = 0;
	while (data->world->map[i])
	{
		printf("%s", data->world->map[i]);
		i++;
	}
	mlx_loop(data->mlx);
	return (0);
}
