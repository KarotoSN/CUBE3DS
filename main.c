/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:12:06 by aarab             #+#    #+#             */
/*   Updated: 2026/04/13 16:10:03 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <math.h>
#include <minilibx-linux/mlx.h>
#include <stdlib.h>

int		world_map[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0,
			0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 1, 0, 0,
			0, 0, 1}, {1, 0, 0, 1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0,
			0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0,
			1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void	clear_draw(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			my_mlx_pixel_put(&cube->img, x, y, 0);
			x++;
		}
		y++;
	}
}
void	prep_rayon(t_cube *cube, int x)
{
	cube->camera_x = 2 * x / 800.0 - 1;
	cube->ray_dir_x = cube->dir_x + cube->plane_x * cube->camera_x;
	cube->ray_dir_y = cube->dir_y + cube->plane_y * cube->camera_x;
	cube->hypo_dist_x = fabs(1 / cube->ray_dir_x);
	cube->hypo_dist_y = fabs(1 / cube->ray_dir_y);
}

void	step(t_cube *cube)
{
	if (cube->ray_dir_x < 0)
	{
		cube->step_x = -1;
		cube->side_dist_x = (cube->player_x - (int)cube->player_x)
			* cube->hypo_dist_x;
	}
	if (cube->ray_dir_x > 0)
	{
		cube->step_x = 1;
		cube->side_dist_x = (((int)cube->player_x + 1.0) - cube->player_x)
			* cube->hypo_dist_x;
	}
	if (cube->ray_dir_y < 0)
	{
		cube->step_y = -1;
		cube->side_dist_y = (cube->player_y - (int)cube->player_y)
			* cube->hypo_dist_y;
	}
	if (cube->ray_dir_y > 0)
	{
		cube->step_y = 1;
		cube->side_dist_y = (((int)cube->player_y + 1.0) - cube->player_y)
			* cube->hypo_dist_y;
	}
}

void	dda(t_cube *cube)
{
	int	hit;

	cube->map_x = (int)cube->player_x;
	cube->map_y = (int)cube->player_y;
	hit = 0;
	while (hit == 0)
	{
		if (cube->side_dist_x < cube->side_dist_y)
		{
			cube->side_dist_x += cube->hypo_dist_x;
			cube->map_x += cube->step_x;
			cube->side = 0;
		}
		else
		{
			cube->side_dist_y += cube->hypo_dist_y;
			cube->map_y += cube->step_y;
			cube->side = 1;
		}
		if (world_map[cube->map_y][cube->map_x] == 1)
			hit = 1;
	}
}
void	wall_distance(t_cube *cube)
{
	if (cube->side == 0)
		cube->wall_dist = cube->side_dist_x - cube->hypo_dist_x;
	else
		cube->wall_dist = cube->side_dist_y - cube->hypo_dist_y;
}

void	calc_line(t_cube *cube)
{
	cube->line_height = (int)(600 / cube->wall_dist);
	cube->draw_start = 300 - (cube->line_height / 2);
	if (cube->draw_start < 0)
		cube->draw_start = 0;
	cube->draw_end = 300 + (cube->line_height / 2);
	if (cube->draw_end >= 600)
		cube->draw_end = 599;
}

void	draw_column(t_cube *cube, int x)
{
	int	y;

	y = 0;
	while (y < 600)
	{
		if (y < cube->draw_start)
			my_mlx_pixel_put(&cube->img, x, y, 0x0087FF);
		else if (y <= cube->draw_end)
			my_mlx_pixel_put(&cube->img, x, y, 0x8B4513);
		else
			my_mlx_pixel_put(&cube->img, x, y, 0xDEB887);
		y++;
	}
}
void	move(t_cube *cube)
{
	int	x;

	x = 0;
	clear_draw(cube);
	while (x < 800)
	{
		prep_rayon(cube, x);
		step(cube);
		dda(cube);
		wall_distance(cube);
		calc_line(cube);
		draw_column(cube, x);
		x++;
	}
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img.img, 0, 0);
}

int	input_manage(int key, t_cube *cube)
{
	double	rot_speed;
	double	old_dir;
	double	move_speed;
	double	old_plane_x;

	move_speed = 0.1;
	rot_speed = 0.1;
	old_dir = cube->dir_x;
	if (key == 65307)
		exit(0);
	if (key == 119)
	{
		cube->player_x += cube->dir_x * move_speed;
		cube->player_y += cube->dir_y * move_speed;
		move(cube);
	}
	if (key == 115)
	{
		cube->player_x -= cube->dir_x * move_speed;
		cube->player_y -= cube->dir_y * move_speed;
		move(cube);
	}
	if (key == 100)
	{
		cube->dir_x = cube->dir_x * cos(rot_speed) - cube->dir_y
			* sin(rot_speed);
		cube->dir_y = old_dir * sin(rot_speed) + cube->dir_y * cos(rot_speed);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(rot_speed) - cube->plane_y
			* sin(rot_speed);
		cube->plane_y = old_plane_x * sin(rot_speed) + cube->plane_y
			* cos(rot_speed);
		move(cube);
	}
	if (key == 97)
	{
		cube->dir_x = old_dir * cos(-rot_speed) - cube->dir_y * sin(-rot_speed);
		cube->dir_y = old_dir * sin(-rot_speed) + cube->dir_y * cos(-rot_speed);
		old_plane_x = cube->plane_x;
		cube->plane_x = cube->plane_x * cos(-rot_speed) - cube->plane_y
			* sin(-rot_speed);
		cube->plane_y = old_plane_x * sin(-rot_speed) + cube->plane_y
			* cos(-rot_speed);
		move(cube);
	}
	return (0);
}

int	main(void)
{
	t_cube cube;

	cube.player_y = 5.5;
	cube.player_x = 5.5;
	cube.dir_x = 1.0;
	cube.dir_y = 0.0;
	cube.plane_x = 0.0;
	cube.plane_y = 0.66;

	cube.mlx = mlx_init();
	if (!cube.mlx)
		return (1);
	cube.img.img = mlx_new_image(cube.mlx, 800, 600);
	cube.img.addr = mlx_get_data_addr(cube.img.img, &cube.img.bits_per_pixel,
			&cube.img.line_lenght, &cube.img.endian);

	cube.win = mlx_new_window(cube.mlx, 800, 600, "CUBE");
	if (!cube.win)
		return (1);
	mlx_hook(cube.win, 2, 1L << 0, input_manage, &cube);
	move(&cube);
	mlx_loop(cube.mlx);
	return (0);
}