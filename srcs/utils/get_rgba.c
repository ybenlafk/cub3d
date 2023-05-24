/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgba.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:58:21 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/24 14:33:39 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0 || a > 255 || a < 0)
        ft_error("Error\n🚨: Invalid colors\n");
    return (r << 24 | g << 16 | b << 8 | a);
}

int get_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}
