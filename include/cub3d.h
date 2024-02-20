/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:44:05 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/20 22:12:12 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#  define DEBUG 0
#  define SHADER 1

# include "player.h"
# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdint.h>
# include <time.h>
# include <sys/time.h>
# include <stdbool.h>

//	Messages & Errors
# define ERR_ARGC		"cub3d: wrong number of arguments. Use only a map path\n"
# define ERR_MALLOC		"cub3d: malloc() failed\n"
# define ERR_MLX_INIT	"cub3d: mlx_init() failed\n"
# define ERR_FD			"cub3d: file opening failed\n"
# define ERR_MLX_WIN	"cub3d: mlx_new_window() failed\n"
# define ERR_MAP		"cub3d: invalid map\n"
# define ERR_IMG		"cub3d: Image failed loading\n"
# define ERR_TIME		"cub3d: timestamp failed\n"
# define MSG_EXIT		"cub3d: Thank you for testing!\n"
# define MSG_LOSE		"cub3d: You lost!\n"

// enemy fov
# define ENEMY_FOV 30
# define ENEMY_SPD 0.025


//	Screen Resolution
# define WIN_WIDTH		900
# define WIN_HEIGHT		600
# define WIN_TITLE		"Cub3D - fda-est & rvaz"

# define TEXTURE_WIDTH	64
# define TEXTURE_HEIGHT	64

# define MM_WIDTH	320
# define MM_HEIGHT	320

# define MM_TILE_WIDTH	32
# define MM_TILE_HEIGHT	32

//	Frame rate in ms

# define FRAME_RATE 40

//	Colors

# define SKY_COLOR				0x005274ff
# define WALL_COLOR				0x00aeb5d1
# define FLOOR_COLOR			0x000c1126
# define CHROMA_KEY_COLOR		0x00ff00ff

# define M_PI			3.14159265358979323846

typedef enum s_image_arr
{
	NO_IMG,
	EA_IMG,
	SO_IMG,
	WE_IMG,
	F_IMG,
	C_IMG,
	MMW_IMG,
	MMF_IMG,
	MMV_IMG,
	EF0_IMG,
	EF1_IMG,
	EF2_IMG,
	EF3_IMG,
	EF4_IMG,
	EF5_IMG,
	EF6_IMG,
	EL0_IMG,
	EL1_IMG,
	EL2_IMG,
	EL3_IMG,
	EL4_IMG,
	EL5_IMG,
	EL6_IMG,
	EB0_IMG,
	EB1_IMG,
	EB2_IMG,
	EB3_IMG,
	EB4_IMG,
	EB5_IMG,
	EB6_IMG,
	ER0_IMG,
	ER1_IMG,
	ER2_IMG,
	ER3_IMG,
	ER4_IMG,
	ER5_IMG,
	ER6_IMG,
	D0_IMG,
	D1_IMG,
	D2_IMG,
	D3_IMG,
	D4_IMG,
	D5_IMG,
	D6_IMG,
}				t_image_arr;

typedef enum s_sprite_type
{
	SPRT_OBJ1,
	SPRT_OBJ2,
	SPRT_ENEMY,
	SPRT_DOOR,
}				t_sprite_type;

typedef struct s_2d_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_vector
{
	t_point	point_a;
	t_point	point_b;
}	t_vector;

typedef struct s_map
{
	char		**map;
	char		**minimap;
	t_point		size;
}				t_map;

typedef struct s_ray
{
	t_point		dir;
	t_point		last_hit;
	double		distance;
	int			wall_height;
	int			side;
	// linked list of hit points
}				t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
	int		**color_grid;
}				t_img;

/**
 * @brief Structure that holds file content and file names
*/
typedef struct s_file
{
	char	**file;
	char	*north_file;
	char	*east_file;
	char	*south_file;
	char	*west_file;
	char	*ceiling_file;
	char	*floor_file;
}				t_file;

typedef struct s_sprite
{
	t_point	pos;
	t_point	dir;
	t_point	coliders[2];
	t_img	*texture;
	bool	move;
	bool	follow;
	double	dist_player;
	short	current_frame;
	short	type;
}				t_sprite;

typedef struct s_player
{
	int			move;
	int			move_cam;
	t_point		mouse;
	int			mouse_toggle;
	t_point		pos;
	t_point		dir;
	t_point		mov_dir;
	t_point		plane;
	double		fov;
	int			vertical;
}				t_player;

/**
 * @brief Structure that holds all the data needed for the program
*/
typedef struct s_data
{
	void		*mlx;			//	put in "t_mlx" struct (?)
	void		*mlx_win;		//	put in "t_mlx" struct (?)
	void		*mlx_win_mm;	//	to be removed
	t_img		*img;			//	put in "t_mlx" struct (?)
	t_img		*img_mm;		//	to be removed (no it cant be)
	t_file		*file;
	t_map		map;
	t_player	player;
	t_sprite	*sprites;
	int 		*sprite_order;
	int			sprite_amt;
	t_img		**textures;
	uint64_t	start_time;
	double		*z_buffer;
	uint64_t	next_frame;		
}				t_data;

/* =====================================================================*
 *		/src/controls/													*
 * =====================================================================*/

//			controls.c
void		set_move(int keycode, t_data *data);
void		set_move_cam(int keycode, t_data *data);

//			actions.c
int			vertical_movement(t_player *player);
int			rotate_player(t_player *player);
int			adjust_fov(t_player *player);
int			move_player(t_data *data);
void		toggle_mouse(t_data *data);

//			hooks.c
int			game_update(t_data *data);
int			key_reader(int keycode, t_data *data);
int			key_release(int keycode, t_player *player);
int			mouse_reader(int x, int y, t_player *player);
int			close_pgm(t_data *data);

/* =====================================================================*
 *		/src/minimap/													*
 * =====================================================================*/

//			minimap.c
void		minimap(t_data *data);

/* =====================================================================*
 *		/src/parsing/													*
 * =====================================================================*/

//			map_check_utils
void		map_and_player_init(t_data *data);

//			map_check.c
void		map_check(t_data *data);

//			parser_2.c
void		identifier_init(t_data *data);

//			parser.c
void		parser(t_data *data, char *str);

//			texture_parser.c
void		texture_parser(t_data *data);

//			enemy_parser.c
void		enemy_parser(t_data *data);

/* =====================================================================*
 *		/src/raycast/													*
 * =====================================================================*/

//			dda.c
void		dda_enemy(t_ray *ray, t_data *data);
void		dda(t_ray *ray, t_data *data);

//			raycat.c
void		raycast(t_data *data);
void		enemy_raycast(t_data *data, t_sprite *enemy);

//			rc_spritecast.c
void		rc_sprites(t_data *data);

/* =====================================================================*
 *		/src/enemy/														*
 * =====================================================================*/

//		enemy.c
void		enemy(t_data *data);

//		enemy_utils.c
void		rotate_enemy(t_sprite *enemy, double angle);


/* =====================================================================*
 *		/src/utils/														*
 * =====================================================================*/

//			utils.c
void		initializer(t_data *data);
int			coordinate_finder(char **mtx, char c, char axle);
int			display_error(char *str);
int			is_inside_map(t_point point, t_point map_size);
int 		is_player(t_point point, t_data *data);
int			is_wall(t_point point, t_data *data);
void		update_view(t_data *data);
void		begining_time_stamp(t_data *data);
uint64_t	time_stamp(t_data *data);

//			utils_2.c
t_point	vector_add(t_point v1, t_point v2);
void		vector_norm(t_point *vector);
t_point	vector_rotate(t_point vector, double angle);
void		rotate_point(t_point *point, double angle);

//			draw_line.c
void		draw_vertical_line(t_point start, int size, t_img *img,
				int color);
void		draw_vertical_line_texture(t_point start, t_img *texture,
				t_data *data, t_ray *ray);
void		draw_vert_line_grad_center(t_img *img, int x, int vertical);

//			draw_pixel.c
void		draw_pixel(t_img *img, int x, int y, int color);

//			free.c
void		free_data(t_data *data);
void		free_file(t_file *file);
void		free_and_exit(t_data *data, char *msg, int exit_status);

//			initializer.c
void		initializer(t_data *data);

//			initializer_textures.c
void		texture_array_init(t_data *data);

int		shader(int color, double distance, double a, double b, short mode);

#endif
