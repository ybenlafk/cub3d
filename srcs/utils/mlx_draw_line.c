/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:58:35 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/19 18:07:28 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void    ft_init(t_var *p, t_line t)
{
    p->dx = abs(t.x1 - t.x0);
	p->dy = abs(t.y1 - t.y0);
    p->sx = get_x_y(t.x0, t.x1);
    p->sy = get_x_y(t.y0, t.y1);
	p->err = get_err(p->dx, p->dy) / 2;
}


void mlx_draw_line(mlx_image_t *image, t_line t, int color)
{
	t_var p;

	ft_init(&p, t);
	if (t.x0 == t.x1 && t.y0 == t.y1)
		mlx_put_pixel(image, t.x0, t.y0, color);
	if (t.x0 < 0 || t.y0 < 0 || t.x1 < 0 || t.y1 < 0)
		return ;
	while (1)
	{
		mlx_put_pixel(image, t.x0, t.y0, color);
		if (t.x0 == t.x1 && t.y0 == t.y1)
			break ;
		p.e2 = p.err;
		if (p.e2 > -p.dx)
		{
			p.err -= p.dy;
			t.x0 += p.sx;
		}
		if (p.e2 < p.dy)
		{
			p.err += p.dx;
			t.y0 += p.sy;
		}
	}
}