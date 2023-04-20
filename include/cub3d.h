/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:34:22 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/04/20 00:46:00 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "libft.h"
#include "get_next_line.h"

#define ERROR 0
#define SUCCESS 1
#define WIDTH 1080
#define HEIGHT 720

typedef	struct	s_world
{
	int			width;
	int			height;
	char		**map;
}				t_world;

typedef struct	s_data
{
	void		*mlx;
	t_world		*world;
}				t_data;

// parse.c
void	init_parse(t_data *data, char *map_fi);


#endif