/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:34:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/25 17:19:12 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 2)
		return (1);			// Error handling
	initializer(&data);
	parser(&data, argv[1]);
	mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	raycast(&data);
	free_and_exit(&data, NULL);
}
