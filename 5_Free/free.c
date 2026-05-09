/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 12:45:42 by aarab             #+#    #+#             */
/*   Updated: 2026/05/09 12:40:04 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	free_cube(t_cube *cube)
{
	if (cube->map.map)
		free_tab(cube->map.map);
	if (cube->map.no_t)
		free(cube->map.no_t);
	if (cube->map.so_t)
		free(cube->map.so_t);
	if (cube->map.we_t)
		free(cube->map.we_t);
	if (cube->map.ea_t)
		free(cube->map.ea_t);
	if (cube->map.ciel_color)
		free(cube->map.ciel_color);
	if (cube->map.floor_color)
		free(cube->map.floor_color);
	if (cube->sprites)
    {
        free(cube->sprites);
        cube->sprites = NULL;
    }
}

void flush_gnl(int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line != NULL)
    {
        free(line);
        line = get_next_line(fd);
    }
}
