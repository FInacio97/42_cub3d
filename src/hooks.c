/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:44:31 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/26 02:19:00 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(int keycode, t_data *data)
{
	if (keycode == MOVE_FORWARD)
		data->player.pos = (t_2d_point){data->player.pos.x + data->player.dir.x, data->player.pos.y + data->player.dir.y};
	else if (keycode == MOVE_BACK)
		data->player.pos = (t_2d_point){data->player.pos.x - data->player.dir.x, data->player.pos.y - data->player.dir.y};
	else if (keycode == MOVE_LEFT)
		data->player.pos = (t_2d_point){data->player.pos.x - data->player.dir.y, data->player.pos.y - data->player.dir.x};
	else if (keycode == MOVE_RIGHT)
		data->player.pos = (t_2d_point){data->player.pos.x + data->player.dir.y, data->player.pos.y + data->player.dir.x};
	printf("newpos: %f %f, dir %f %f\n", data->player.pos.x, data->player.pos.y, data->player.dir.x, data->player.dir.y);
}

void	adjust_fov(int keycode, t_data *data)
{
	if (keycode == ZOOM_IN)
		data->player.fov -= 3;
	else if (keycode == ZOOM_OUT)
		data->player.fov += 3;
}

void	rotate_player(int keycode, t_data *data)
{
	if (keycode == ROT)
		rotate_point(&data->player.dir, 2);
	else if (keycode == RROT)
		rotate_point(&data->player.dir, -2);
}

int	key_reader(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_pgm(data);
	else if (keycode == MOVE_FORWARD || keycode == MOVE_BACK
		|| keycode == MOVE_LEFT || keycode == MOVE_RIGHT)
		move_player(keycode, data);
	else if (keycode == ZOOM_OUT || keycode == ZOOM_IN)
		adjust_fov(keycode, data);
	else if (keycode == ROT || keycode == RROT)
		rotate_player(keycode, data);
	// ft_bzero(data->img->addr, (WIN_WIDTH * WIN_HEIGHT)
	// 	* sizeof(data->img->bits_per_pixel));
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	return (0);
}

int	close_pgm(t_data *data)
{
	printf("Program closing\n");
	free_and_exit(data, MSG_EXIT, 0);
	return (0);
}
