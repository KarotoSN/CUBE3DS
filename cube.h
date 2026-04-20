/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 11:46:30 by aarab             #+#    #+#             */
/*   Updated: 2026/04/20 16:39:27 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <math.h>
# include <minilibx-linux/mlx.h>
# include <stdlib.h>
# include <string.h>

extern int	world_map[10][10];

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
	double	hypo_ray_dist_y;
	double	hypo_ray_dist_x;
	double	wall_dist_x;
	double	wall_dist_y;
	double	wall_dist;
	int		side_x;
	int		side_y;
	int		map_x;
	int		map_y;
	int		side;
	int		draw_start;
	int		draw_end;
	int		line_height;
}			t_cube;

int			init_mlx(t_cube *cube);
void		init_engine(t_cube *cube);
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
void		prep_rayon(t_cube *cube, int x);
void		step(t_cube *cube);
void		dda(t_cube *cube);
void		wall_dist(t_cube *cube);
void		calc_line(t_cube *cube);
void		clear_screan(t_cube *cube);
void		draw_colomn(t_cube *cube, int x);
void		move(t_cube *cube);
void		rotation(t_cube *cube, int val);
int			input_manage(int key, t_cube *cube);
void		letsgo(t_cube *cube, int o);

#endif