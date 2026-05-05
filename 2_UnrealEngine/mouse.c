/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 14:04:53 by aarab             #+#    #+#             */
/*   Updated: 2026/05/01 17:34:48 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	mouse_move(int x, int y, t_cube *cube)
{
	double	x_prime;
	double	rotation_speed;

	(void)y;
	x_prime = x - 400;
	if (x_prime == 0)
		return (0);
	rotation_speed = x_prime * 0.02;
	rotation(cube, rotation_speed);
	mlx_mouse_move(cube->mlx, cube->win, 400, 300);
	return (0);
}
