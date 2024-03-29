/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:36:08 by ybenlafk          #+#    #+#             */
/*   Updated: 2023/05/23 15:36:26 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}