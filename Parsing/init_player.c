/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:34:36 by aarab             #+#    #+#             */
/*   Updated: 2026/05/02 17:50:18 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_player_plane(t_cube *cube, int x, int y)
{
	if (cube->map.map[y][x] == 'N')
	{
		cube->plane_x = 0.66;
		cube->plane_y = 0.0;
		return ;
	}
	else if (cube->map.map[y][x] == 'S')
	{
		cube->plane_x = -0.66;
		cube->plane_y = 0.0;
		return ;
	}
	else if (cube->map.map[y][x] == 'W')
	{
		cube->plane_x = 0.0;
		cube->plane_y = -0.66;
		return ;
	}
	else if (cube->map.map[y][x] == 'E')
	{
		cube->plane_x = 0.0;
		cube->plane_y = 0.66;
		return ;
	}
}

void	set_player_dir(t_cube *cube, int x, int y)
{
	if (cube->map.map[y][x] == 'N')
	{
		cube->dir_x = 0.0;
		cube->dir_y = -1.0;
		return ;
	}
	else if (cube->map.map[y][x] == 'S')
	{
		cube->dir_x = 0.0;
		cube->dir_y = 1.0;
	}
	else if (cube->map.map[y][x] == 'W')
	{
		cube->dir_x = -1.0;
		cube->dir_y = 0.0;
		return ;
	}
	else if (cube->map.map[y][x] == 'E')
	{
		cube->dir_x = 1.0;
		cube->dir_y = 0.0;
	}
}

void	find_player(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (cube->map.map[y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (cube->map.map[y][x] && ft_strchr("NSWE", cube->map.map[y][x]))
			{
				cube->player_x = x + 0.5;
				cube->player_y = y + 0.5;
				set_player_dir(cube, x, y);
				set_player_plane(cube, x, y);
				cube->map.map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
