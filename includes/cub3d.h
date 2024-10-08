/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:26:03 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/23 17:44:32 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "constant_variables.h"

# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <X11/keysym.h>

# ifndef DOOR_VALID
#  define DOOR_VALID 0
# endif

typedef enum e_maptype
{
	SPACE,
	WALL,
	VOID,
	START_NORTH,
	START_SOUTH,
	START_EAST,
	START_WEST,
	DOOR,
	DOOR_WESTEAST,
	DOOR_NORTHSOUTH,
	UNKNOWN
}	t_maptype;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_textures;

typedef struct s_element
{
	char	*string;
	void	*variable;
	bool	(*validate_func)(void *, char *);
}	t_element;

typedef struct s_player
{
	size_t	x_arr;
	size_t	y_arr;
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_draw_line
{
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
	int	start_y;
	int	start_x;
	int	end_x;
	int	end_y;
	int	error;
	int	error2;	
}	t_draw_line;

typedef struct s_ray
{
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_walldist;
	int		stepx;
	int		stepy;
	int		side;
	int		mapx;
	int		mapy;
	double	pos_x;
	double	pos_y;
	bool	door;
}	t_ray;

typedef struct s_set_pixel
{
	int	x;
	int	y;
	int	color;
}	t_set_pixel;

typedef struct s_raycasting
{
	double	fov;
	double	ray_angle;
	double	angle_step;
	double	start_angle;
	float	diff_angle;
	float	perp_walldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	wall_x;
	int		i;
}	t_raycasting;

typedef struct s_img_rendering
{
	void	*img_ptr;
	char	*img_data;
	int		color;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		size_line;
	int		bpp;
	int		endian;
}	t_img_rendering;

typedef struct s_wall
{
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		endian;
	int		line_length;
	int		img_height;
	int		img_width;
}	t_wall;

typedef struct s_sprite
{
	void	*xpm;
	int		width;
	int		height;
	void	*xpm_data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_sprite;

typedef struct s_mouse_pos
{
	int	x;
	int	y;
}	t_mouse_pos;

typedef struct s_minimap
{
	int	x;
	int	y;
	int	y_arr;
	int	x_arr;
	int	count_y;
	int	count_x;

}	t_minimap;

typedef struct s_walls
{
	t_wall			wall_n;
	t_wall			wall_s;
	t_wall			wall_e;
	t_wall			wall_w;
	t_wall			door;
}	t_walls;

typedef enum e_door_state
{
	OPENING,
	CLOSING,
	IDLE,
	NO_DOOR
}	t_door_state;

typedef struct s_door
{
	double			percent_closed;
	t_door_state	state;
}	t_door;

typedef struct s_cub3d
{
	t_textures		textures;
	t_element		elements[6];
	int				floor_color;
	int				ceiling_color;
	t_player		player;
	t_maptype		**map;
	t_door			**doors;
	size_t			map_height;
	size_t			map_width;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_sprite		sprites[5];
	size_t			sprite_index;
	t_img_rendering	img;
	t_ray			ray;
	float			move;
	t_mouse_pos		mouse_pos;
	t_walls			walls;
	bool			mouse_disabled;
	bool			texture_flipped;
	int				safecs;
}	t_cub3d;

// set pixel

void		set_pixel(char *img_data,
				t_set_pixel pixel, int size_line, int bpp);
void		set_the_pixel_looping(t_cub3d *game, t_img_rendering *img);
void		set_pixel_variables(t_set_pixel *pixel, int color, int x, int y);

// draw map

void		draw_map(t_cub3d *game, t_img_rendering *img);
void		draw_line(t_cub3d *game, t_draw_line *ray, int color);
void		draw_vertical_line(t_cub3d *game,
				int x, int drawstart, int drawend);
void		draw_floor_and_ceiling(t_cub3d *game,
				int x, int drawstart, int drawend);
void		draw_wall(t_cub3d *game,
				t_raycasting *var, t_wall *current_wall, t_ray *ray);

// rending

void		rend_minimap(t_cub3d *game, t_img_rendering *img);
void		rend_player_on_the_minimap(t_cub3d *game, t_img_rendering *img);

// events

int			handle_keypress(int keycode, t_cub3d *game);
int			handle_loop_hook(t_cub3d *game);
bool		mouse_pos_changed(t_cub3d *game);
int			handle_mouse_click(int button, int x, int y, t_cub3d *game);
void		check_doors(t_cub3d *game);
bool		update_doors(t_cub3d *game);
int			wa(int keycode, t_cub3d *game);
void		close_open_door(t_cub3d *game,
				size_t posy, size_t posx, bool *redraw);
int			w(int keycode, t_cub3d *game);
int			a(int keycode, t_cub3d *game);
int			s(int keycode, t_cub3d *game);
int			d(int keycode, t_cub3d *game);

// check

int			is_wall(const t_cub3d *game, float x, float y, bool checkDiagonal);
bool		close_to_door(size_t y1, size_t x1, size_t y2, size_t x2);

// raycast

void		cast_ray(t_ray *ray, t_cub3d *game, t_raycasting *var);
void		cast_all_rays(t_cub3d *game);
t_wall		*get_current_wall(t_cub3d *game, t_raycasting *var, t_ray *ray);
void		get_wall_height(t_raycasting *var);

// utils.c

void		skip_spaces(const char *str, size_t *index);
void		free_all(t_cub3d *cub3d, int fd);
void		errmsg(char *str);
void		t_abs(int number);
void		destroy_images_free_sprite(t_cub3d *game);
void		destroy_images(t_cub3d *game);
void		destroy_image(void *mlx_ptr, void **img_ptr);

// map_parsing/open.c

int			open_map(int argc, char **argv);

// map_parsing/elements.c

void		init_elements(t_cub3d *cub3d);

// map_parsing/read.c

bool		read_map(int argc, char **argv, t_cub3d *cub3d);

// map_parsing/fill.c

void		fill_map(t_cub3d *cub3d, const t_string *map_string);

// map_parsing/validate.c

t_string	*validate_map_end(int fd, t_string **map_string);
bool		valid_chars(t_cub3d *cub3d, const char *line,
				const t_string *map_str);
bool		map_closed(const t_cub3d *cub3d);

// map_parsing/validate2.c
bool		is_start(t_maptype type);
bool		only_space(char *str);

// map_parsing/utils.c
void		remove_linebreak(char *str);
t_string	*return_string(t_string *map_string);

// sprites.c
void		free_sprites(t_cub3d *game);
bool		load_sprites(t_cub3d *game);
void		put_sprite_to_image(t_cub3d *game);

// walls_check.c
bool		going_through_walls_check(const t_cub3d *game,
				int new_y, int new_x);
bool		too_close_to_wall(const t_cub3d *game, int y, int x);

// main.c
bool		validate_texture(void *ptr, char *line);

#endif
