/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 08:56:49 by aarab             #+#    #+#             */
/*   Updated: 2026/05/02 17:42:16 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	player_check(t_cube *cube)
{
	int	x;
	int	y;
	int	find;

	find = 0;
	x = 0;
	y = 0;
	while (cube->map.map[y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (cube->map.map[y][x] == 'N' || cube->map.map[y][x] == 'S'
				|| cube->map.map[y][x] == 'E' || cube->map.map[y][x] == 'W')
				find += 1;
			x++;
		}
		y++;
	}
	if (find == 1)
		return (1);
	return (0);
}

int	wall_check(t_cube *cube)
{
	int	x;
	int	y;

	y = -1;
	while (cube->map.map[++y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (cube->map.map[y][x] == 'N' || cube->map.map[y][x] == 'S'
				|| cube->map.map[y][x] == 'E' || cube->map.map[y][x] == 'W'
				|| cube->map.map[y][x] == '0')
			{
				if (y == 0 || x == 0 || cube->map.map[y + 1] == NULL
					|| cube->map.map[y][x + 1] == '\0')
					return (0);
				if (cube->map.map[y + 1][x] == ' ' || cube->map.map[y][x
					+ 1] == ' ' || cube->map.map[y][x - 1] == ' '
					|| cube->map.map[y - 1][x] == ' ')
					return (0);
			}
			x++;
		}
	}
	return (1);
}
