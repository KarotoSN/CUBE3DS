/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:09:19 by aarab             #+#    #+#             */
/*   Updated: 2026/05/09 12:27:15 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
int	extract_map(t_cube *cube, int map_fichier, char *line)
{
	char	*mega_string;
	char	*temp;
	int		empty_flag;

	empty_flag = 0;
	mega_string = ft_strdup("");
	while (line != NULL)
	{
		if (empty_line(line) == 1)
			empty_flag = 1;
		else if (empty_flag == 1)
		{
			printf("Error\nLa map est séparée par une ligne vide.\n");
			free(line);
			free(mega_string);
			return (0);
		}
		temp = mega_string;
		mega_string = ft_strjoin(temp, line);
		free(temp);
		free(line);
		line = get_next_line(map_fichier);
	}
	cube->map.map = ft_split(mega_string, '\n');
	free(mega_string);
	format_map(cube);
	return (1);
}

static int	parse_nswe(t_cube *cube, char *line)
{
	if (line[0] == '\n')
		return (1);
	if (!ft_strncmp(line, "NO", 2))
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
		return (0);
	return (1);
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
		if (!parse_nswe(cube, line))
		{
			if (extract_map(cube, map_fichier, line) == 0)
			{
				free_cube(cube);
				flush_gnl(map_fichier);
				close(map_fichier);
				exit(0);
			}
			break ;
		}
		free(line);
		line = get_next_line(map_fichier);
	}
	close(map_fichier);
}

static void	copy_map_line(char *s, char *s_old, int max)
{
	int	j;

	j = -1;
	while (s_old[++j])
		s[j] = s_old[j];
	while (j < max)
		s[j++] = ' ';
	s[j] = '\0';
}

void	format_map(t_cube *cube)
{
	char	**new_map;
	int		max_len;
	int		i;

	i = -1;
	max_len = 0;
	while (cube->map.map[++i])
	{
		if (max_len < (int)ft_strlen(cube->map.map[i]))
			max_len = (int)ft_strlen(cube->map.map[i]);
	}
	new_map = malloc(sizeof(char *) * (i + 1));
	if (!new_map)
		return ;
	new_map[i] = NULL;
	while (--i >= 0)
	{
		new_map[i] = malloc(max_len + 1);
		if (!new_map[i])
			free_tab(new_map);
		copy_map_line(new_map[i], cube->map.map[i], max_len);
	}
	free_tab(cube->map.map);
	cube->map.map = new_map;
}
