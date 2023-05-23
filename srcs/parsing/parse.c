/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:24:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/23 19:36:19 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty(char c)
{
	if (c == '\n' || c == ' ' || c == 0)
		return (1);
	return (0);
}

int	is_valid(t_var *p, char **map)
{
	if (!map[p->i + 1] || p->j == 0)
		return (1);
	else if (!map[p->i - 1] || p->i == 0)
		return (1);
	else if (is_empty(map[p->i + 1][p->j + 1]))
		return (1);
	else if (is_empty(map[p->i - 1][p->j - 1]))
		return (1);
	else if (is_empty(map[p->i - 1][p->j + 1]))
		return (1);
	else if (is_empty(map[p->i + 1][p->j - 1]))
		return (1);
	else if (is_empty(map[p->i][p->j + 1]))
		return (1);
	else if (is_empty(map[p->i][p->j - 1]))
		return (1);
	else if (is_empty(map[p->i + 1][p->j]))
		return (1);
	else if (is_empty(map[p->i - 1][p->j]))
		return (1);
	return (0);
}

int	is_surrounded(char **map)
{
	t_var	p;

	p.i = 0;
	while (map[p.i])
	{
		p.j = 0;
		while (map[p.i][p.j] && map[p.i][p.j] != '\n')
		{
			if (map[p.i][p.j] != '1' && map[p.i][p.j] != ' '
				&& map[p.i][p.j] != '\t')
				if (is_valid(&p, map))
					return (1);
			p.j++;
		}
		p.i++;
	}
	return (0);
}

void	parse_params(t_data *data, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->world.no = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->world.so = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->world.we = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->world.ea = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		data->world.floor_c = ft_strdup(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		data->world.ceil_c = ft_strdup(line + 2);
}

void	init_parse(t_data *data, char *map_fi)
{
	int fd;
	int i;
	char *line;

	i = 0;
	if (ft_strcmp(".cub", map_fi + (ft_strlen(map_fi) - 4)))
		exit(0);
	fd = open(map_fi, O_RDONLY);
	if (fd < 0)
		exit(0);
	line = get_next_line(fd);

	data->world.map = (char **)ft_calloc(1, sizeof(char *));
	if (!data->world.map || fd < 0)
		exit(0);
	while (line && *line)
	{
		parse_params(data, line);
		if (line && *line && is_map(line))
		{
			data->world.map[i] = ft_strdup(line);
			i++;
			data->world.map = ft_realloc(data->world.map, (i + 1)
					* sizeof(char *));
		}
		free(line);
		line = get_next_line(fd);
	}
	data->world.map[i] = NULL;
	// if (is_surrounded(data->world.map))
	// {
	// 	printf("Error\n");
	// 	exit(0);
	// }
	close(fd);
}