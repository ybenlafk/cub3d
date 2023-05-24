/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:24:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/24 14:39:28 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str)
{
	printf("%s", str);
	exit(0);
}

int	is_empty(char c)
{
	if (c == '\n' || c == ' ' || c == 0)
		return (1);
	return (0);
}

int	is_valid(t_var *p, char **map)
{
	if (!map[p->i + 1] || p->j == 0 || map[p->i + 1][0] == '\n')
		return (1);
	else if (!map[p->i - 1] || p->i == 0 || map[p->i - 1][0] == '\n')
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
			if (map[p.i][p.j] == '0')
				if (is_valid(&p, map))
					return (1);
			p.j++;
		}
		p.i++;
	}
	return (0);
}
void	parse_params_2(t_data *data, char *line, int *is)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		data->world.floor_c = ft_strtrim(line + 2, " \t\n");
		(*is)++;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		data->world.ceil_c = ft_strtrim(line + 2, " \t\n");
		(*is)++;
	}
}

void	parse_params(t_data *data, char *line, int *is)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		data->world.no = ft_strtrim(line + 3, " \t\n");
		(*is)++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		data->world.so = ft_strtrim(line + 3, " \t\n");
		(*is)++;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		data->world.we = ft_strtrim(line + 3, " \t\n");
		(*is)++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		data->world.ea = ft_strtrim(line + 3, " \t\n");
		(*is)++;
	}
	else
		parse_params_2(data, line, is);
}

void	is_valid_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] != 'N' && map[i][j] != 'S'
			&& map[i][j] != 'E' && map[i][j] != 'W'
			&& map[i][j] != '0' && map[i][j] != '1'
			&& map[i][j] != ' ' && map[i][j] != '\t'
			&& map[i][j] != '\n')
				ft_error("Error\n");
			j++;
		}
		i++;
	}
}

void	check_player(t_data *data)
{
	int	i;
	int	j;
	int cut;

	cut = 0;
	i = 0;
	while (data->world.map[i])
	{
		j = 0;
		while (data->world.map[i][j] && data->world.map[i][j] != '\n')
		{
			if (data->world.map[i][j] == 'N' || data->world.map[i][j] == 'S' ||
				data->world.map[i][j] == 'E' || data->world.map[i][j] == 'W')
				cut++;
			j++;
		}
		i++;
	}
	if (cut != 1)
		ft_error("Error\n");
}

void	fill_data(t_data *data, char *line, int fd, int is)
{
	int	i;

	i = 0;
	while (line && *line && !is_map(line))
	{
		parse_params(data, line, &is);
		free(line);
		line = get_next_line(fd);
	}
	if (is != 6)
			exit(0);
	while (line && *line)
	{
		if (!is_map(line))
			ft_error("Error\n");
		if (line && *line)
		{
			data->world.map[i] = ft_strdup(line);
			data->world.map = ft_realloc(data->world.map, (++i + 1)
					* sizeof(char *));
		}
		free(line);
		line = get_next_line(fd);
	}
	data->world.map[i] = NULL;
}

void	init_parse(t_data *data, char *map_fi)
{
	int fd;
	char *line;
	static int is;

	if (ft_strcmp(".cub", map_fi + (ft_strlen(map_fi) - 4)))
		ft_error("Error\n");
	fd = open(map_fi, O_RDONLY);
	if (fd < 0)
		ft_error("Error\nFd error\n");
	line = get_next_line(fd);
	data->world.map = (char **)ft_calloc(1, sizeof(char *));
	if (!data->world.map || !line)
		ft_error("Error\n");
	fill_data(data, line, fd, is);
	check_player(data);
	is_valid_map(data->world.map);
	if (is_surrounded(data->world.map))
		ft_error("Error\n");
	close(fd);
}
