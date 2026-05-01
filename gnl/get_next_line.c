/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:46:55 by aarab             #+#    #+#             */
/*   Updated: 2026/04/25 16:19:36 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	*ft_delete(char *gnl)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (gnl[i] && gnl[i] != '\n')
		i++;
	if (!gnl[i])
	{
		return (free(gnl), NULL);
	}
	str = malloc(ft_strlen2(gnl) - i + 1);
	if (!str)
	{
		free(gnl);
		return (NULL);
	}
	if (gnl[i] == '\n')
		i++;
	while (gnl[i])
		str[j++] = gnl[i++];
	str[j] = '\0';
	free(gnl);
	return (str);
}

static char	*ft_result(char *gnl)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!gnl || !*gnl)
		return (NULL);
	while (gnl[i] && gnl[i] != '\n')
		i++;
	if (gnl[i] == '\n')
		i++;
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (j < i)
	{
		res[j] = gnl[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

static char	*read_stock(int fd, char *gnl)
{
	char	*temp;
	char	*new_gnl;
	int		len;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	len = 1;
	while (len > 0)
	{
		len = read(fd, temp, BUFFER_SIZE);
		if (len < 0)
			return (free(gnl), free(temp), NULL);
		if (len == 0)
			break ;
		temp[len] = '\0';
		new_gnl = ft_strjoin2(gnl, temp);
		if (!new_gnl)
			return (free(gnl), free(temp), NULL);
		gnl = new_gnl;
		if (ft_strchr2(gnl, '\n'))
			break ;
	}
	free(temp);
	return (gnl);
}

char	*get_next_line(int fd)
{
	char		*res;
	static char	*gnl;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	gnl = read_stock(fd, gnl);
	if (!gnl)
		return (NULL);
	res = ft_result(gnl);
	gnl = ft_delete(gnl);
	return (res);
}
