/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:09:27 by aarab             #+#    #+#             */
/*   Updated: 2026/04/20 16:40:08 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	rotation(t_cube *cube, int val)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	if (val == 1)
		rot_speed = -0.1;
	else
		rot_speed = 0.1;
	old_dir_x = cube->dir_x;
	cube->dir_x = cube->dir_x * cos(rot_speed) - cube->dir_y * sin(rot_speed);
	cube->dir_y = old_dir_x * sin(rot_speed) + cube->dir_y * cos(rot_speed);
	old_plane_x = cube->plane_x;
	cube->plane_x = cube->plane_x * cos(rot_speed) - cube->plane_y
		* sin(rot_speed);
	cube->plane_y = old_plane_x * sin(rot_speed) + cube->plane_y
		* cos(rot_speed);
}

void	letsgo(t_cube *cube, int o)
{
	if (o)
	{
		cube->player_x += cube->dir_x * -0.1;
		cube->player_y += cube->dir_y * -0.1;
	}
	else
	{
		cube->player_x -= cube->dir_x * 0.1;
		cube->player_y -= cube->dir_y * 0.1;
	}
}

int	input_manage(int key, t_cube *cube)
{
	if (key == 65307)
		exit(1);
	if (key == 119)
	{
		letsgo(t_cube * cube, int 1) move(cube);
	}
	if (key == 115)
	{
		letsgo(t_cube * cube, int 0) move(cube);
	}
	if (key == 97)
	{
		rotation(cube, 1);
		rotation(cube, 1);
		move(cube);
	}
	if (key == 100)
	{
		rotation(cube, 0);
		rotation(cube, 0);
		move(cube);
	}
	return (0);
}
