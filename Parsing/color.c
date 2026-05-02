/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:36:38 by aarab             #+#    #+#             */
/*   Updated: 2026/05/02 17:50:02 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_and_convert(char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error\nNegatif color, impossible l'ami\n");
		return (-1);
	}
	return ((r << 16) | (g << 8) | b);
}

int	get_rgb_color(char *string_rgb)
{
	char	**rgb;
	int		r;
	int		color;

	r = 0;
	rgb = ft_split(string_rgb, ',');
	if (!rgb)
		return (1);
	while (rgb[r])
		r++;
	if (r != 3)
	{
		printf("Error\nFaut mettre R,G,B");
		free_tab(rgb);
		return (-1);
	}
	color = check_and_convert(rgb);
	free_tab(rgb);
	return (color);
}
