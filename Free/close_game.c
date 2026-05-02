/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 12:48:46 by aarab             #+#    #+#             */
/*   Updated: 2026/05/02 16:39:49 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	close_game(t_cube *cube)
{
	free_tab(cube->map.map);
	free(cube->map.no_t);
	free(cube->map.so_t);
	free(cube->map.we_t);
	free(cube->map.ea_t);
	free(cube->map.ciel_color);
	free(cube->map.floor_color);
	mlx_destroy_image(cube->mlx, cube->texture_hill.img);
	mlx_destroy_image(cube->mlx, cube->sonic.img);
	mlx_destroy_image(cube->mlx, cube->bendi.img);
	mlx_destroy_image(cube->mlx, cube->chaos.img);
	mlx_destroy_image(cube->mlx, cube->img.img);
	mlx_mouse_show(cube->mlx, cube->win);
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit(0);
	return (0);
}
