/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:45:29 by aarab             #+#    #+#             */
/*   Updated: 2026/04/27 16:48:23 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	prep_rayon(t_cube *cube, int x)
{
	cube->camera_x = 2 * x / 800.0 - 1;
	cube->ray_dir_x = cube->dir_x + (cube->plane_x * cube->camera_x);
	cube->ray_dir_y = cube->dir_y + (cube->plane_y * cube->camera_x);
	cube->hypo_ray_dist_x = fabs(1 / cube->ray_dir_x);
	cube->hypo_ray_dist_y = fabs(1 / cube->ray_dir_y);
}

void	step(t_cube *cube)
{
	if (cube->ray_dir_x < 0)
	{
		cube->side_x = -1;
		cube->wall_dist_x = (cube->player_x - (int)cube->player_x)
			* cube->hypo_ray_dist_x;
	}
	if (cube->ray_dir_x > 0)
	{
		cube->side_x = 1;
		cube->wall_dist_x = ((int)cube->player_x + 1.0 - cube->player_x)
			* cube->hypo_ray_dist_x;
	}
	if (cube->ray_dir_y < 0)
	{
		cube->side_y = -1;
		cube->wall_dist_y = (cube->player_y - (int)cube->player_y)
			* cube->hypo_ray_dist_y;
	}
	if (cube->ray_dir_y > 0)
	{
		cube->side_y = 1;
		cube->wall_dist_y = ((int)cube->player_y + 1.0 - cube->player_y)
			* cube->hypo_ray_dist_y;
	}
}

void	dda(t_cube *cube)
{
	int	hit;

	hit = 0;
	cube->map_x = (int)cube->player_x;
	cube->map_y = (int)cube->player_y;
	while (hit == 0)
	{
		if (cube->wall_dist_x < cube->wall_dist_y)
		{
			cube->wall_dist_x += cube->hypo_ray_dist_x;
			cube->map_x += cube->side_x;
			cube->side = 0;
		}
		else
		{
			cube->wall_dist_y += cube->hypo_ray_dist_y;
			cube->map_y += cube->side_y;
			cube->side = 1;
		}
		if (cube->map.map[cube->map_y] && cube->map.map[cube->map_y][cube->map_x] == '1')
			hit = 1;
	}
}

void	wall_dist(t_cube *cube)
{
	if (cube->side == 0)
		cube->wall_dist = cube->wall_dist_x - cube->hypo_ray_dist_x;
	else
		cube->wall_dist = cube->wall_dist_y - cube->hypo_ray_dist_y;
}
