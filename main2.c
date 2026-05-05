/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:24:09 by aarab             #+#    #+#             */
/*   Updated: 2026/05/04 11:02:24 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void check_args(int ac, char **av)
{
	char	*str;

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
}
int	main(int ac, char **av)
{
	t_cube	cube;

	check_args(ac, av);
	ft_bzero(&cube, sizeof(t_cube));
	if (parse_all(&cube, av[1]) == 0)
	{
		free_cube(&cube);
		return (printf("Error\nMap mal integrer l'ami !"), 1);
	}
	if (init_mlx(&cube))
	{
		free_cube(&cube);
		return (1);
	}
	mlx_hook(cube.win, 2, 1L << 0, key_press, &cube);
	mlx_hook(cube.win, 3, 1L << 1, key_release, &cube);
	mlx_loop_hook(cube.mlx, game_loop, &cube);
	mlx_hook(cube.win, 6, 1L << 6, mouse_move, &cube);
	mlx_hook(cube.win, 17, 0, close_game, &cube);
	mlx_loop(cube.mlx);
}
