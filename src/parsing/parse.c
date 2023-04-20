/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:57:36 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/04/20 03:23:47 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_params(t_data *data, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->world->no = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->world->so = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->world->we = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->world->ea = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		data->world->floor_c = ft_strdup(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		data->world->ceil_c = ft_strdup(line + 2);
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
	while (line && *line)
	{
		parse_params(data, line);
		if (line && *line && is_map(line))
		{
			data->world->map[i] = ft_strdup(line);
			i++;
			data->world->map = ft_realloc(data->world->map, (i + 1)
					* sizeof(char *));
		}
		free(line);
		line = get_next_line(fd);
	}
	data->world->map[i] = NULL;
	close(fd);
}