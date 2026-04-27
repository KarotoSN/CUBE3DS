/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarab <aarab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 11:46:30 by aarab             #+#    #+#             */
/*   Updated: 2026/04/27 17:15:49 by aarab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}			t_data;

typedef struct s_text
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}			t_text;

typedef struct s_map
{
	char	**map;
	char	*no_t;
	char	*so_t;
	char	*ea_t;
	char	*we_t;
	char	*floor_color;
	char	*ciel_color;
	int		floor;
	int		ciel;

}			t_map;
typedef struct s_cube
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_data	img;
	t_text	texture_hill;
	t_text	sonic;
	t_text	bendi;
	t_text	chaos;
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
	double	tex_pos;
	double	step;
	int		tex_x;
	int		tex_y;
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
void		colision(t_cube *cube, int o);
char		*get_next_line(int fd);
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_strchr2(const char *s1, int c);
size_t		ft_strlen2(const char *s);
void		extract_map(t_cube *cube, int map_fichier, char *line);
void		config_search(t_cube *cube, char *fichier);
void		format_map(t_cube *cube);
int			get_rgb_color(char *string_rgb);
void		find_player(t_cube *cube);
int			wall_check(t_cube *cube);
int			parse_all(t_cube *cube, char *map);
int			player_check(t_cube *cube);
char		*get_next_line(int fd);
void		clean_newline(char *str);

#endif