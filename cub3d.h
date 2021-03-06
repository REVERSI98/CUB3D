/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 14:20:11 by aamzil            #+#    #+#             */
/*   Updated: 2020/02/25 22:14:59 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include "mlx.h"
# include "gnl/get_next_line.h"
# include "error_handling/error_handling.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

# define RAD(X) (X * (M_PI / (float)180))
# define DEGREE(X) ((X * 360) / 2 * M_PI)
# define FOV_ANGLE RAD(60)
# define MIN_MAP 0.05
# define MAP_READED 0
# define MAP_EMPTY_LINE 1

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S 4

typedef	struct		s_save_memories
{
	void						*memory;
	struct s_save_memories		*next;
}					t_save_memories;

typedef struct		s_map
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*img_data;
}					t_map;

typedef struct		s_player
{
	int			x;
	int			y;
	int			walk_dir;
	float		walk_speed;
	float		rotate_angle;
	int			rotate_dir;
	float		rotate_speed;
	float		ray_long;
	int			move_side;
	int			nb_player;
}					t_player;

typedef	struct		s_ray
{
	float		ray_distance;
	float		ray_angle;
	int			hit_vertical;
	float		hit_x;
	float		hit_y;
	int			facing_down;
	int			facing_left;
}					t_ray;

typedef struct		s_hexa_color{
	int red;
	int green;
	int blue;
}					t_hexa_color;

typedef struct		s_file_info
{
	int				win_width;
	int				win_height;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
	t_hexa_color	floor_color;
	t_hexa_color	ceilling_color;
}					t_file_info;

typedef struct		s_map_from_file
{
	struct s_map_from_file	*next;
	char					*line;
}					t_map_from_file;

typedef struct		s_texture_data
{
	void			*img;
	int				**data_img;
}					t_texture_data;

typedef struct		s_sprite
{
	int				x;
	int				y;
	float			dist;
	float			angle;
	int				size;
}					t_sprite;

typedef struct		s_rgb
{
	double			r;
	double			g;
	double			b;
}					t_rgb;

typedef struct		s_header_info
{
	int					width_in_bytes;
	char				header[54];
	unsigned int		bitcount;
	unsigned int		imagesize;
	unsigned int		bi_size;
	unsigned int		bf_off_bits;
	unsigned int		filesize;
	unsigned int		bi_planes;
	unsigned char		*buf;
}					t_header_info;

t_map				g_map;
t_player			g_player;
t_ray				*g_all_rays;
t_file_info			g_file_info;
t_map_from_file		*g_map_list;
t_texture_data		g_tex;
t_sprite			*g_sprites;
t_save_memories		*g_all_memories;

int					g_map_read_check[2];

float				g_y_vert_inter;
float				g_x_vert_inter;
float				g_x_vert_step;
float				g_y_vert_step;

float				g_y_horz_inter;
float				g_x_horz_inter;
float				g_x_horz_step;
float				g_y_horz_step;

int					**g_world_map;
int					g_map_width;
int					g_map_height;
float				g_box_size;
int					g_num_rays;
int					g_mini_map;
int					g_nb_sprites;

int					g_duplicate[8];
int					g_error;
char				*g_error_msg;
int					g_is_screen_shot;
int					g_total_data;

char				*g_file_path;

int					draw();
void				render3d();
void				my_clear();
int					skip_numbers(char *str);
void				treat_resolution();
void				main_read_func();
t_hexa_color		read_hexa_file(char *line);
t_map_from_file		*ft_create_list(char *line);
void				ft_add_back(t_map_from_file **node, char *line);
void				treat_map(char *line);
int					ft_list_size(t_map_from_file *node);
void				fill_map();
void				check_the_rgb();
void				treat_sprites();
float				normalize_angle(float angle);
float				calc_distance(float x, float y);
void				mlx_pixel_put_img(int x, int y, int color);
float				calc_distance(float x, float y);
void				generate_sprite();
void				create_bitmap();
int					get_pixel_from_img(int x, int y);
void				init_error();
int					skip_spaces(char *str);
int					get_pixel_from_img(int x, int y);
t_save_memories		*ft_create_list_mem(void *memory);
void				ft_add_back_mem(t_save_memories **node, void *memory);
void				*my_malloc(size_t size);
void				clear_memory(t_save_memories *node);
int					is_hit_wall(float x, float y);
void				render_line(float final_point, float angle);
void				render_map();
void				render_player();
int					key_release(int key);
int					event_handler(int key);
int					destroy();
void				init_player();
void				cast_ray();
void				render();
int					rgb_to_hexa(int r, int g, int b);
void				rect(float x, float y, float height, int texture_off_x);
void				angle_size_sprite(int i);
void				is_screen_shot(int argc, char **argv);
void				texture_data();
void				init_mlx_var();
void				valid_rgb_format(char *line);
void				fill_texture_var(char *line, int tex);
void				check_line(char *line);

#endif
