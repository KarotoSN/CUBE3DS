/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:30:37 by aarab             #+#    #+#             */
/*   Updated: 2026/05/07 14:12:56 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 800 || y < 0 || y >= 600)
		return ;
	dst = img->addr + (y * img->line_lenght + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	load_tex(t_cube *cube, t_text *tex, char *path, char *err)
{
	int	width;
	int	height;

	tex->img = mlx_xpm_file_to_image(cube->mlx, path, &width, &height);
	if (!tex->img)
	{
		printf("%s\n", err);
		return (1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_lenght, &tex->endian);
	return (0);
}

int	init_texture(t_cube *cube)
{
	clean_newline(cube->map.no_t);
	clean_newline(cube->map.so_t);
	clean_newline(cube->map.we_t);
	clean_newline(cube->map.ea_t);
	if (load_tex(cube, &cube->texture_hill, cube->map.no_t,
			"Error\nNO texture failed"))
		return (1);
	if (load_tex(cube, &cube->sonic, cube->map.so_t,
			"Error\nSO texture failed"))
		return (1);
	if (load_tex(cube, &cube->bendi, cube->map.ea_t,
			"Error\nEA texture failed"))
		return (1);
	if (load_tex(cube, &cube->chaos, cube->map.we_t,
			"Error\nWE texture failed"))
		return (1);
	if (load_tex(cube, &cube->sprite_text, "Textures/py.xpm",
			"Error\nSprite texture failed"))
		return (1);
	return (0);
}

int	init_mlx(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
		return (1);
	if (init_texture(cube))
		return (1);
	cube->img.img = mlx_new_image(cube->mlx, 800, 600);
	cube->img.addr = mlx_get_data_addr(cube->img.img, &cube->img.bits_per_pixel,
			&cube->img.line_lenght, &cube->img.endian);
	cube->win = mlx_new_window(cube->mlx, 800, 600, "Silent Hmir");
	if (!cube->win)
		return (1);
	mlx_mouse_hide(cube->mlx, cube->win);
	return (0);
}
