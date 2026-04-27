/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:30:44 by aarab             #+#    #+#             */
/*   Updated: 2026/04/27 17:13:12 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	clean_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			return ;
		}
		i++;
	}
}
int	parse_all(t_cube *cube, char *map)
{
	int	rgb_floor;
	int	rgb_ciel;

	config_search(cube, map);
	rgb_ciel = ft_atoi(cube->map.ciel_color);
	rgb_floor = ft_atoi(cube->map.floor_color);
	cube->map.floor = get_rgb_color(cube->map.ciel_color);
	cube->map.ciel = get_rgb_color(cube->map.floor_color);
	if (cube->map.floor == -1 || cube->map.ciel == -1)
		return (0);
	if (player_check(cube) == 0)
		return (0);
	find_player(cube);
	if (wall_check(cube))
		return (0);
	return (1);
}
