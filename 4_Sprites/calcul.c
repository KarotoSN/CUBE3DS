/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:22:24 by aarab             #+#    #+#             */
/*   Updated: 2026/05/07 13:50:51 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	sprite_sort(t_cube *cube)
{
	int			i;
	int			j;
	double		d1;
	double		d2;
	t_sprites	temp;

	i = -1;
	while (++i < cube->sprites_count)
	{
		j = i;
		while (j < cube->sprites_count)
		{
			d1 = pow(cube->player_x - cube->sprites[i].x, 2)
				+ pow(cube->player_y - cube->sprites[i].y, 2);
			d2 = pow(cube->player_x - cube->sprites[j].x, 2)
				+ pow(cube->player_y - cube->sprites[j].y, 2);
			if (d1 < d2)
			{
				temp = cube->sprites[i];
				cube->sprites[i] = cube->sprites[j];
				cube->sprites[j] = temp;
			}
			j++;
		}
	}
}

static void	calc_sprite(t_cube *cube, t_calc_spr *spr, int i)
{
	spr->x = cube->sprites[i].x - cube->player_x;
	spr->y = cube->sprites[i].y - cube->player_y;
	spr->inv_det = 1 / (cube->plane_x * cube->dir_y - cube->plane_y
			* cube->dir_x);
	spr->trans_x = spr->inv_det * (cube->dir_y * spr->x - cube->dir_x * spr->y);
	spr->trans_y = spr->inv_det * (-cube->plane_y * spr->x + cube->plane_x
			* spr->y);
	spr->screen_x = (int)(800 / 2) * (1 + (spr->trans_x / spr->trans_y));
	spr->height = abs((int)(600 / spr->trans_y));
	spr->start_y = (-spr->height / 2) + (600 / 2);
	if (spr->start_y < 0)
		spr->start_y = 0;
	spr->end_y = (spr->height / 2) + (600 / 2);
	if (spr->end_y >= 600)
		spr->end_y = 599;
	spr->width = abs((int)(600 / spr->trans_y));
	spr->start_x = (-spr->width / 2) + spr->screen_x;
	if (spr->end_x < 0)
		spr->end_x = 0;
	spr->end_x = (spr->width / 2) + spr->screen_x;
	if (spr->end_x >= 800)
		spr->end_x = 799;
}

static void	draw_sprites(t_calc_spr *spr, t_cube *cube)
{
	int		x;
	int		y;
	int		color;
	char	*pixel;

	x = spr->start_x;
	while (x < spr->end_x)
	{
		if (spr->trans_y > 0 && x > 0 && x < 800
			&& spr->trans_y < cube->z_buffer[x])
		{
			spr->tex_x = ((int)((x - (-spr->width / 2 + spr->screen_x)) * 64.0
						/ spr->width));
			spr->step = 64.0 / spr->height;
			spr->tex_pos = (spr->start_y - 300 + spr->height / 2) * spr->step;
			y = spr->start_y;
			while (y < spr->end_y)
			{
				spr->tex_y = (int)spr->tex_pos & 63;
				spr->tex_pos += spr->step;
				pixel = cube->sprite_text.addr + (spr->tex_y
						* cube->sprite_text.line_lenght + spr->tex_x
						* (cube->sprite_text.bits_per_pixel / 8));
				color = *(unsigned int *)pixel;
				if (color != 0x000000)
					my_mlx_pixel_put(&cube->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

void	render_sprite(t_cube *cube)
{
	int			i;
	t_calc_spr	spr;

	i = 0;
	ft_bzero(&spr, sizeof(t_calc_spr));
	sprite_sort(cube);
	while (i < cube->sprites_count)
	{
		calc_sprite(cube, &spr, i);
		draw_sprites(&spr, cube);
		i++;
	}
}
