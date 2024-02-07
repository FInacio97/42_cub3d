/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/07 14:29:07 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_column(t_data *data, int r, t_ray *ray)
{
	int		sky_size;
	t_img	*texture;

	if (ray->side == 0)
	{
		if (ray->dir.x < 0)
			texture = &data->image.west_img;
		else
			texture = &data->image.east_img;
	}
	else
	{
		if (ray->dir.y < 0)
			texture = &data->image.north_img;
		else
			texture = &data->image.south_img;
	}
	sky_size = ((WIN_HEIGHT - ray->wall_height) / 2) + data->player.vertical;
	draw_vert_line_grad_center(data->img, r, data->player.vertical);
	draw_vertical_line_texture((t_2d_point){r, sky_size}, texture, data, ray);
}

/**
 * @brief	The raycast main function
*/
void	raycast(t_data *data)
{
	t_ray		ray;
	double		camera_x;
	int			r;
	
	r = 0;
	while (r < WIN_WIDTH)
	{
		camera_x = 2 * r / (double)WIN_WIDTH - 1;
		ray.dir.x = data->player.dir.x + data->player.plane.x * camera_x;
		ray.dir.y = data->player.dir.y + data->player.plane.y * camera_x;
		dda(&ray, data);
		ray.wall_height = WIN_HEIGHT / (ray.distance * (data->player.fov * 0.0151));
		draw_column(data, r, &ray);
		r++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}
