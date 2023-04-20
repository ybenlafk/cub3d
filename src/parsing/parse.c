/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:57:36 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/04/20 01:02:00 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map(char *line)
{
	return (*line == '1' || *line == '\t' || *line == ' ');
}

void	init_parse(t_data *data, char *map_fi)
{
	int fd;
	int i;
	char *line;

	i = 0;
	fd = open(map_fi, O_RDONLY);
	line = get_next_line(fd);
	data->world = (t_world *)ft_calloc(1, sizeof(t_world));
	data->world->map = (char **)ft_calloc(1, sizeof(char *));
	if (!data->world || !data->world->map || fd < 0)
		return ;
	while (line)
	{
		if (line && *line && is_map(line))
		{
			data->world->map[i] = ft_strdup(line);
			i++;
			data->world->map = ft_realloc(data->world->map, (i + 1)
					* sizeof(char *));
		}
		line = get_next_line(fd);
		free(line);
	}
	data->world->map[i] = NULL;
	close(fd);
}