/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawland.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:41:34 by aarab             #+#    #+#             */
/*   Updated: 2026/05/07 14:11:28 by aarab            ###   ########.fr       */
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

static t_text	*texture_choice(t_cube *cube)
{
	if (cube->side)
	{
		if (cube->ray_dir_y < 0)
			return (&cube->texture_hill);
		else
			return (&cube->sonic);
	}
	else
	{
		if (cube->ray_dir_x < 0)
			return (&cube->bendi);
		else
			return (&cube->chaos);
	}
}

void	draw_colomn(t_cube *cube, int x)
{
	int		y;
	int		color;
	char	*pixel;
	t_text	*r_texture;

	r_texture = texture_choice(cube);
	y = 0;
	while (y < 600)
	{
		if (y < cube->draw_start)
			my_mlx_pixel_put(&cube->img, x, y, cube->map.ciel);
		else if (y <= cube->draw_end)
		{
			cube->tex_y = (int)cube->tex_pos & 63;
			cube->tex_pos += cube->step;
			pixel = r_texture->addr + (cube->tex_y * r_texture->line_lenght
					+ cube->tex_x * (r_texture->bits_per_pixel / 8));
			color = *(unsigned int *)pixel;
			color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&cube->img, x, y, color);
		}
		else
			my_mlx_pixel_put(&cube->img, x, y, cube->map.floor);
		y++;
	}
}

void	move(t_cube *cube)
{
	int	x;

	x = 0;
	while (x < 800)
	{
		prep_rayon(cube, x);
		step(cube);
		dda(cube);
		wall_dist(cube);
		cube->z_buffer[x] = cube->wall_dist;
		calc_line(cube);
		draw_colomn(cube, x);
		x++;
	}
	render_sprite(cube);
}
