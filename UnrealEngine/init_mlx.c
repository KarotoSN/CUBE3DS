/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:30:37 by aarab             #+#    #+#             */
/*   Updated: 2026/05/01 16:58:51 by aarab            ###   ########.fr       */
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

void	init_texture(t_cube *cube)
{
	int	width;
	int	height;

	clean_newline(cube->map.no_t);
	clean_newline(cube->map.so_t);
	clean_newline(cube->map.we_t);
	clean_newline(cube->map.ea_t);
	printf("Chemin testé : [%s]\n", cube->map.no_t);
	cube->texture_hill.img = mlx_xpm_file_to_image(cube->mlx, cube->map.no_t,
			&width, &height);
	if (cube->texture_hill.img == NULL)
	{
		printf("lol");
		exit(1);
	}
	cube->texture_hill.addr = mlx_get_data_addr(cube->texture_hill.img,
			&cube->texture_hill.bits_per_pixel, &cube->texture_hill.line_lenght,
			&cube->texture_hill.endian);
	cube->sonic.img = mlx_xpm_file_to_image(cube->mlx, cube->map.so_t, &width,
			&height);
	if (cube->sonic.img == NULL)
	{
		printf("lol2");
		exit(1);
	}
	cube->sonic.addr = mlx_get_data_addr(cube->sonic.img,
			&cube->sonic.bits_per_pixel, &cube->sonic.line_lenght,
			&cube->sonic.endian);
	cube->bendi.img = mlx_xpm_file_to_image(cube->mlx, cube->map.ea_t, &width,
			&height);
	if (cube->bendi.img == NULL)
	{
		printf("Chemin testé : [%s]\n", cube->map.ea_t);
		printf("lol3");
		exit(1);
	}
	cube->bendi.addr = mlx_get_data_addr(cube->bendi.img,
			&cube->bendi.bits_per_pixel, &cube->bendi.line_lenght,
			&cube->bendi.endian);
	cube->chaos.img = mlx_xpm_file_to_image(cube->mlx, cube->map.we_t, &width,
			&height);
	if (cube->chaos.img == NULL)
	{
		printf("lol4");
		exit(1);
	}
	cube->chaos.addr = mlx_get_data_addr(cube->chaos.img,
			&cube->chaos.bits_per_pixel, &cube->chaos.line_lenght,
			&cube->chaos.endian);
}
int	init_mlx(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
		return (1);
	init_texture(cube);
	cube->img.img = mlx_new_image(cube->mlx, 800, 600);
	cube->img.addr = mlx_get_data_addr(cube->img.img, &cube->img.bits_per_pixel,
			&cube->img.line_lenght, &cube->img.endian);
	cube->win = mlx_new_window(cube->mlx, 800, 600, "CUBE");
	if (!cube->win)
		return (1);
	mlx_mouse_hide(cube->mlx, cube->win);
	return (0);
}
