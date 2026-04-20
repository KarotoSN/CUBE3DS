/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawland.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:41:34 by aarab             #+#    #+#             */
/*   Updated: 2026/04/20 16:41:48 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calc_line(t_cube *cube)
{
	cube->line_height = (int)(600 / cube->wall_dist);
	cube->draw_start = (int)300 - (cube->line_height / 2);
	if (cube->draw_start < 0)
		cube->draw_start = 0;
	cube->draw_end = (int)300 + (cube->line_height / 2);
	if (cube->draw_end > 599)
		cube->draw_end = 599;
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
	int	y;
	int	color;

	if (cube->side)
		color = 0x5D2E0D;
	else
		color = 0x8B4513;
	y = 0;
	while (y < 600)
	{
		if (y < cube->draw_start)
			my_mlx_pixel_put(&cube->img, x, y, 0x0087FF);
		else if (y <= cube->draw_end)
			my_mlx_pixel_put(&cube->img, x, y, color);
		else
			my_mlx_pixel_put(&cube->img, x, y, 0xDEB887);
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
