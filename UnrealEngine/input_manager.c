/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:09:27 by aarab             #+#    #+#             */
/*   Updated: 2026/05/01 17:26:04 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	rotation(t_cube *cube, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cube->dir_x;
	cube->dir_x = cube->dir_x * cos(rot_speed) - cube->dir_y * sin(rot_speed);
	cube->dir_y = old_dir_x * sin(rot_speed) + cube->dir_y * cos(rot_speed);
	old_plane_x = cube->plane_x;
	cube->plane_x = cube->plane_x * cos(rot_speed) - cube->plane_y
		* sin(rot_speed);
	cube->plane_y = old_plane_x * sin(rot_speed) + cube->plane_y
		* cos(rot_speed);
}
void	colision(t_cube *cube, int o)
{
	double	future_x;
	double	future_y;
	double	speed;

	if (o)
		speed = 0.010;
	else
		speed = -0.010;
	future_x = cube->player_x + cube->dir_x * speed;
	future_y = cube->player_y + cube->dir_y * speed;
	if (cube->map.map[(int)cube->player_y][(int)future_x] == '0')
		cube->player_x = future_x;
	if (cube->map.map[(int)future_y][(int)cube->player_x] == '0')
		cube->player_y = future_y;
}
void	colision_cote(t_cube *cube, int o)
{
	double	future_x;
	double	future_y;
	double	speed;

	speed = 0.010;
	if (o == 1)
	{
		future_x = cube->player_x + cube->plane_x * speed;
		future_y = cube->player_y + cube->plane_y * speed;
	}
	else
	{
		future_x = cube->player_x - cube->plane_x * speed;
		future_y = cube->player_y - cube->plane_y * speed;
	}
	if (cube->map.map[(int)cube->player_y][(int)future_x] == '0')
		cube->player_x = future_x;
	if (cube->map.map[(int)future_y][(int)cube->player_x] == '0')
		cube->player_y = future_y;
}

int	key_press(int key, t_cube *cube)
{
	if (key == 119) // W / Z
		cube->key_w = 1;
	if (key == 115) // S
		cube->key_s = 1;
	if (key == 97) // A / Q
		cube->key_a = 1;
	if (key == 100) // D
		cube->key_d = 1;
	if (key == 65307) // ECHAP
		exit(0);
	return (0);
}
int	key_release(int key, t_cube *cube)
{
	if (key == 119) // W / Z
		cube->key_w = 0;
	if (key == 115) // S
		cube->key_s = 0;
	if (key == 97) // A / Q
		cube->key_a = 0;
	if (key == 100) // D
		cube->key_d = 0;
	if (key == 65307) // ECHAP
		exit(0);
	return (0);
}

int	game_loop(t_cube *cube)
{
	if (cube->key_w == 1)
		colision(cube, 1);
	if (cube->key_s == 1)
		colision(cube, 0);
	if (cube->key_d == 1)
		colision_cote(cube, 1);
	if (cube->key_a == 1)
		colision_cote(cube, 0);
	move(cube);
	return (0);
}
