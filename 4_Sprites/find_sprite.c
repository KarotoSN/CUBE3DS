/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:44:04 by aarab             #+#    #+#             */
/*   Updated: 2026/05/04 11:52:29 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	count_sprites(t_cube *cube)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = -1;
	while (cube->map.map[++y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (cube->map.map[y][x] == '2')
				count++;
			x++;
		}
	}
	return (count);
}

int	init_sprites(t_cube *cube)
{
	int x;
	int y;
	int i;

	cube->sprites_count = count_sprites(cube);
	if (cube->sprites_count == 0)
		return (1);
	cube->sprites = malloc(sizeof(t_sprites) * cube->sprites_count);
	if (!cube->sprites)
		return (0);
	i = 0;
	y = -1;
	while (cube->map.map[++y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (cube->map.map[y][x] == '2')
			{
				cube->sprites[i].x = x + 0.5;
				cube->sprites[i].y = y + 0.5;
				i++;
			}
			x++;
		}
	}
	return (1);
}