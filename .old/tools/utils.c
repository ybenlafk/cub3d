/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:06:19 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/05/18 15:46:34 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    put_str(char *s, int fd)
{
    int i;

    i = 0;
    while (s[i])
        write (fd, &s[i++], 1);
}

void	draw_square(mlx_image_t *image, t_param t, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < t.size)
	{
		j = 0;
		while (j < t.size)
		{
			mlx_put_pixel(image, t.x2 + j, t.y2 + i, color);
			j++;
		}
		i++;
	}
}

void    draw_map_init(t_var p, t_var *var, t_param *t)
{
    var->px = p.j * 32;
	var->py = p.i * 32;
	var->pdx = cos(var->pa) * 5;
	var->pdy = sin(var->pa) * 5;
    t->x0 = var->px;
    t->y0 = var->py;
    t->x1 = var->px + 8 + var->pdx * 8;
    t->y1 = var->py + 8 + var->pdy * 8;
}

void    square_init(t_var p, t_param *t, int size)
{
    t->size = size;
    t->x2 = p.j * 32;
    t->y2 = p.i * 32;
}
void    player_init(t_param *t)
{
    t->size = 16;
    t->x2 = 0;
    t->y2 = 0;
}

void    draw_player(t_data *data, t_var p, t_param *t, t_var *var)
{
    if (data->world->map[p.i][p.j] == 'N'
        || data->world->map[p.i][p.j] == 'S'
		|| data->world->map[p.i][p.j] == 'E'
		|| data->world->map[p.i][p.j] == 'W')
	{
        player_init(t);
		draw_square(var->p, *t, 0xFF0000FF);
		draw_map_init(p, var, t);
		mlx_draw_line(var->line, *t, 0xFFFFFFF);
	}
}

int get_x_y(int x, int y)
{
    if (x < y)
        return (1);
    return (-1);
}
int get_err(int x, int y)
{
    if (x > y)
        return (x);
    return (-y);
}

void    ft_init(t_var *p, t_param t)
{
    p->dx = abs(t.x1 - t.x0);
	p->dy = abs(t.y1 - t.y0);
    p->sx = get_x_y(t.x0, t.x1);
    p->sy = get_x_y(t.y0, t.y1);
	p->err = get_err(p->dx, p->dy) / 2;
}
