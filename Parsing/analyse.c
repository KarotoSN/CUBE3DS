/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:09:19 by aarab             #+#    #+#             */
/*   Updated: 2026/04/27 17:24:10 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	set_player_plane(t_cube *cube, int x, int y)
{
	if (cube->map.map[y][x] == 'N')
	{
		cube->plane_x = 0.66;
		cube->plane_y = 0.0;
		return ;
	}
	else if (cube->map.map[y][x] == 'S')
	{
		cube->plane_x = -0.66;
		cube->plane_y = 0.0;
		return ;
	}
	else if (cube->map.map[y][x] == 'W')
	{
		cube->plane_x = 0.0;
		cube->plane_y = -0.66;
		return ;
	}
	else if (cube->map.map[y][x] == 'E')
	{
		cube->plane_x = 0.0;
		cube->plane_y = 0.66;
		return ;
	}
}

void	set_player_dir(t_cube *cube, int x, int y)
{
	if (cube->map.map[y][x] == 'N')
	{
		cube->dir_x = 0.0;
		cube->dir_y = -1.0;
		return ;
	}
	else if (cube->map.map[y][x] == 'S')
	{
		cube->dir_x = 0.0;
		cube->dir_y = 1.0;
	}
	else if (cube->map.map[y][x] == 'W')
	{
		cube->dir_x = -1.0;
		cube->dir_y = 0.0;
		return ;
	}
	else if (cube->map.map[y][x] == 'E')
	{
		cube->dir_x = 1.0;
		cube->dir_y = 0.0;
	}
}
void	find_player(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (cube->map.map[y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (cube->map.map[y][x] == 'N' || cube->map.map[y][x] == 'S')
			{
				cube->player_x = x + 0.5;
				cube->player_y = y + 0.5;
				set_player_dir(cube, x, y);
				set_player_plane(cube, x, y);
				cube->map.map[y][x] = '0';
				return ;
			}
			if (cube->map.map[y][x] == 'W' || cube->map.map[y][x] == 'E')
			{
				cube->player_x = x + 0.5;
				cube->player_y = y + 0.5;
				set_player_dir(cube, x, y);
				set_player_plane(cube, x, y);
				cube->map.map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	extract_map(t_cube *cube, int map_fichier, char *line)
{
	char	*mega_string;
	char	*temp;
	int		i;

	i = 0;
	mega_string = ft_strdup("");
	while (line != NULL)
	{
		temp = mega_string;
		mega_string = ft_strjoin(temp, line);
		free(temp);
		free(line);
		line = get_next_line(map_fichier);
	}
	cube->map.map = ft_split(mega_string, '\n');
	free(mega_string);
	format_map(cube);
}

void	config_search(t_cube *cube, char *fichier)
{
	int		map_fichier;
	char	*line;

	map_fichier = open(fichier, O_RDONLY);
	if (map_fichier < 0)
	{
		printf("Error\nFaut bien mettre la map l'ami !");
		exit(1);
	}
	line = get_next_line(map_fichier);
	while (line != NULL)
	{
		if (line[0] == '\n')
		{
		}
		else if (!ft_strncmp(line, "NO", 2))
			cube->map.no_t = ft_strdup(line + 3);
		else if (!ft_strncmp(line, "SO", 2))
			cube->map.so_t = ft_strdup(line + 3);
		else if (!ft_strncmp(line, "EA", 2))
			cube->map.ea_t = ft_strdup(line + 3);
		else if (!ft_strncmp(line, "WE", 2))
			cube->map.we_t = ft_strdup(line + 3);
		else if (!ft_strncmp(line, "C ", 2))
			cube->map.ciel_color = ft_strdup(line + 1);
		else if (!ft_strncmp(line, "F ", 2))
			cube->map.floor_color = ft_strdup(line + 1);
		else
		{
			extract_map(cube, map_fichier, line);
			break ;
		}
		free(line);
		line = get_next_line(map_fichier);
	}
	close(map_fichier);
}

void	format_map(t_cube *cube)
{
	char	**new_map;
	int		max_len;
	int		i;
	int		j;
	int		high;

	i = 0;
	max_len = 0;
	while (cube->map.map[i])
	{
		if (max_len < (int)ft_strlen(cube->map.map[i]))
			max_len = (int)ft_strlen(cube->map.map[i]);
		i++;
	}
	new_map = malloc(sizeof(char *) * (i + 1));
	high = i;
	i = 0;
	while (i < high)
	{
		j = 0;
		new_map[i] = malloc(max_len + 1);
		if (!new_map[i])
			return ;
		while (cube->map.map[i][j])
		{
			new_map[i][j] = cube->map.map[i][j];
			j++;
		}
		while (j < max_len)
		{
			new_map[i][j] = ' ';
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	new_map[i] = NULL;
	cube->map.map = new_map;
}