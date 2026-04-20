/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:30:37 by aarab             #+#    #+#             */
/*   Updated: 2026/04/20 13:33:07 by aarab            ###   ########.fr       */
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

int	init_mlx(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
		return (1);
	cube->img.img = mlx_new_image(cube->mlx, 800, 600);
	cube->img.addr = mlx_get_data_addr(cube->img.img, &cube->img.bits_per_pixel,
			&cube->img.line_lenght, &cube->img.endian);
	cube->win = mlx_new_window(cube->mlx, 800, 600, "CUBE");
	if (!cube->win)
		return (1);
	return (0);
}
