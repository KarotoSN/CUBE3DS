/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:06:48 by aarab             #+#    #+#             */
/*   Updated: 2026/05/05 15:50:40 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	draw_square(t_cube *cube, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = 10;
	i = 0;
	if (color == 0xFF0000)
		size = 5;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(&cube->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
void	draw_minimap(t_cube *cube)
{
	int	x;
	int	y;
	int	size;

	size = 7;
	y = -1;
	while (cube->map.map[++y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (cube->map.map[y][x] == '1')
				draw_square(cube, x * size, y * size, 0x3D3634);
			if (cube->map.map[y][x] == '0' || cube->map.map[y][x] == '2')
				draw_square(cube, x * size, y * size, 0x786866);
			x++;
		}
	}
	draw_square(cube, ((int)cube->player_x * size) + 2, ((int)cube->player_y
			* size) + 2, 0xFF0000);
}
