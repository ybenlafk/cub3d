/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:31:48 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/05/19 17:31:48 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_map(char *line)
{
	return (*line == '1' || *line == '0' || *line == '\t' || *line == ' ');
}