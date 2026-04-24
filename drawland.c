/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawland.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:41:34 by aarab             #+#    #+#             */
/*   Updated: 2026/04/23 13:52:27 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calc_line(t_cube *cube)
{
	double	wall_x;

	cube->line_height = (int)(600 / cube->wall_dist);
	cube->draw_start = (int)300 - (cube->line_height / 2);
	if (cube->draw_start < 0)
		cube->draw_start = 0;
	cube->draw_end = (int)300 + (cube->line_height / 2);
	if (cube->draw_end > 599)
		cube->draw_end = 599;
	if (cube->side == 0)
		wall_x = cube->player_y + cube->wall_dist * cube->ray_dir_y;
	else
		wall_x = cube->player_x + cube->wall_dist * cube->ray_dir_x;
	wall_x -= floor(wall_x);
	cube->tex_x = (int)(wall_x * 64.0);
	cube->step = 1.0 * 64.0 / cube->line_height;
	cube->tex_pos = (cube->draw_start - 300 + cube->line_height / 2)
		* cube->step;
}

void	clear_screan(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			my_mlx_pixel_put(&cube->img, x, y, 0x87CEEB);
			x++;
		}
		y++;
	}
}

void	draw_colomn(t_cube *cube, int x)
{
	int		y;
	int		color;
	char	*pixel;
	t_text	*r_texture;

	if (cube->side)
	{
		if (cube->ray_dir_y < 0)
			r_texture = &cube->texture_hill;
		else
			r_texture = &cube->sonic;
	}
	else
	{
		if (cube->ray_dir_x < 0)
			r_texture = &cube->bendi;
		else
			r_texture = &cube->chaos;
	}
	y = 0;
	while (y < 600)
	{
		if (y < cube->draw_start)
			my_mlx_pixel_put(&cube->img, x, y, 0x0087FF);
		else if (y <= cube->draw_end)
		{
			cube->tex_y = (int)cube->tex_pos & 63;
			cube->tex_pos += cube->step;
			pixel = r_texture->addr + (cube->tex_y * r_texture->line_lenght
					+ cube->tex_x * (r_texture->bits_per_pixel / 8));
			color = *(unsigned int *)pixel;
			my_mlx_pixel_put(&cube->img, x, y, color);
		}
		else
			my_mlx_pixel_put(&cube->img, x, y, 0x0f8c12);
		y++;
	}
}

void	move(t_cube *cube)
{
	int	x;

	x = 0;
	clear_screan(cube);
	while (x < 800)
	{
		prep_rayon(cube, x);
		step(cube);
		dda(cube);
		wall_dist(cube);
		calc_line(cube);
		draw_colomn(cube, x);
		x++;
	}
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img.img, 0, 0);
}
