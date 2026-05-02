/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:41:51 by aarab             #+#    #+#             */
/*   Updated: 2026/05/02 16:42:06 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	key_press(int key, t_cube *cube)
{
	if (key == 119)
		cube->key_w = 1;
	if (key == 115)
		cube->key_s = 1;
	if (key == 97)
		cube->key_a = 1;
	if (key == 100)
		cube->key_d = 1;
	if (key == 65307)
		close_game(cube);
	return (0);
}

int	key_release(int key, t_cube *cube)
{
	if (key == 119)
		cube->key_w = 0;
	if (key == 115)
		cube->key_s = 0;
	if (key == 97)
		cube->key_a = 0;
	if (key == 100)
		cube->key_d = 0;
	if (key == 65307)
		close_game(cube);
	return (0);
}
