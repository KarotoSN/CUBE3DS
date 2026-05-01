/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:32:21 by aarab             #+#    #+#             */
/*   Updated: 2026/04/25 16:19:10 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s2)
		return (free(s1), NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (free(s1), NULL);
	i = -1;
	j = 0;
	while (s1[++i])
	{
		res[i] = s1[i];
	}
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (free(s1), res);
}

char	*ft_strchr2(const char *s1, int c)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == (char)c)
		{
			return ((char *)&s1[i]);
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s1[i]);
	return (NULL);
}

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
