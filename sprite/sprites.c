/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <aamzil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:24:28 by aamzil            #+#    #+#             */
/*   Updated: 2020/02/25 11:25:24 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sort_sprites(void)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++i < g_nb_sprites)
	{
		j = i;
		while (++j < g_nb_sprites)
		{
			if (g_sprites[i].dist < g_sprites[j].dist)
			{
				tmp = g_sprites[i];
				g_sprites[i] = g_sprites[j];
				g_sprites[j] = tmp;
			}
		}
	}
}

void	sprite_dist(void)
{
	int i;
	int j;
	int k;

	i = -1;
	k = -1;
	while (++i < g_map_height)
	{
		j = -1;
		while (++j < g_map_width)
		{
			if (g_world_map[i][j] != 2)
				continue;
			g_sprites[++k].dist = calc_distance(j * g_box_size, i * g_box_size);
		}
	}
}

void	render_sprite(float x_offset, float y_offset, t_sprite sprite)
{
	int i;
	int j;
	int color;

	i = -1;
	j = -1;
	while (++i < sprite.size)
	{
		if (x_offset + i < 0 || x_offset + i > g_file_info.win_width)
			continue;
		if (g_all_rays[(int)(x_offset + i)].ray_distance <= sprite.dist)
			continue;
		j = -1;
		while (++j < sprite.size)
		{
			if (y_offset + j < 0 || y_offset + j > g_file_info.win_height)
				continue;
			color = g_tex.data_img[4][(int)(64 * (j * 64 / sprite.size) +
					(i * 64 / sprite.size))];
			if (color)
				mlx_pixel_put_img((x_offset + i), (y_offset + j), color);
		}
	}
}

void	treat_sprites(void)
{
	float	x_offset;
	float	y_offset;
	int		i;

	sprite_dist();
	sort_sprites();
	i = -1;
	while (++i < g_nb_sprites)
	{
		if (g_player.rotate_angle >= 2 * M_PI)
			g_player.rotate_angle = normalize_angle(g_player.rotate_angle);
		g_sprites[i].dist = calc_distance(g_sprites[i].x * g_box_size,
				g_sprites[i].y * g_box_size);
		g_sprites[i].angle = atan2((g_sprites[i].y * g_box_size) - g_player.y,
				(g_sprites[i].x * g_box_size) - g_player.x);
		angle_size_sprite(i);
		x_offset = (g_sprites[i].angle - g_player.rotate_angle) *
			g_file_info.win_width / (FOV_ANGLE) +
			(g_file_info.win_width / 2 - g_sprites[i].size / 2);
		y_offset = g_file_info.win_height / 2 - g_sprites[i].size / 2;
		render_sprite(x_offset, y_offset, g_sprites[i]);
	}
}

void	generate_sprite(void)
{
	int i;
	int j;
	int k;

	g_sprites = (t_sprite*)my_malloc(g_nb_sprites * sizeof(t_sprite));
	i = -1;
	k = -1;
	while (++i < g_map_height)
	{
		j = -1;
		while (++j < g_map_width)
		{
			if (g_world_map[i][j] != 2)
				continue;
			g_sprites[++k].x = j + 1;
			g_sprites[k].y = i + 1;
		}
	}
	treat_sprites();
}
