/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 11:46:30 by aarab             #+#    #+#             */
/*   Updated: 2026/04/13 15:41:39 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}			t_data;

typedef struct s_cube
{
	void	*mlx;
	void	*win;
	t_data	img;
	double	player_x;
	double	player_y;
	double	dir_y;
	double	dir_x;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	camera_x;
	double	ray_dir_y;
	double	hypo_dist_y;
	double	hypo_dist_x;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
	double	wall_dist;
	int		draw_start;
	int		draw_end;
	int		line_height;
}			t_cube;

#endif