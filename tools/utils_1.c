/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:57:24 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/05/18 16:13:40 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    moves(t_data *data, t_var *p)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
        p->speed = 1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        exit(1);
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        p->new_px -= data->p.pdx / p->speed;
        p->new_py -= data->p.pdy / p->speed;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        p->new_px += data->p.pdx / p->speed;
        p->new_py += data->p.pdy / p->speed;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        p->new_px -= data->p.pdy / p->speed;
        p->new_py += data->p.pdx / p->speed;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        p->new_px += data->p.pdy / p->speed;
        p->new_py -= data->p.pdx / p->speed;
    }
}

void    angels(t_data *data)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
    {
        data->p.pa -= 0.05;
        data->p.pdx = cos(data->p.pa) * 5;
        data->p.pdy = sin(data->p.pa) * 5;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
    {
        data->p.pa += 0.05;
        data->p.pdx = cos(data->p.pa) * 5;
        data->p.pdy = sin(data->p.pa) * 5;
    }
    data->p.p->instances[0].x = data->p.px;
    data->p.p->instances[0].y = data->p.py;
}

int get_step(float x)
{
    if (x < 0)
        return (-1);
    return (1);
}
