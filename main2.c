/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:24:09 by aarab             #+#    #+#             */
/*   Updated: 2026/04/27 17:01:41 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int ac, char **av)
{
	t_cube	cube;
	char *str;
	(void)av;
	if (ac != 2)
	{
		printf("Error\nProgramme + fichier.cub");
		exit(1);
	}
	str = ft_strrchr(av[1], '.');
	if (!str || ft_strncmp(str, ".cub", 5))
	{
		printf("Error\nProgramme + fichier.cub");
		exit(1);
	}
	if(parse_all(&cube, av[1]) == 1)
	{
		printf("lol va te faire foutre");
		return(1);
	}
	if (init_mlx(&cube))
		return (1);
	mlx_hook(cube.win, 2, 1L << 0, input_manage, &cube);
	move(&cube);
	mlx_loop(cube.mlx);
}
