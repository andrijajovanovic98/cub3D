/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:44:15 by ajovanov          #+#    #+#             */
/*   Updated: 2024/09/24 10:44:17 by ajovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	init_ray(t_ray *ray, double ray_angle, double x, double y)
{
	ray->raydir_x = cos(ray_angle);
	ray->raydir_y = sin(ray_angle);
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
	if (ray->raydir_x < 0)
	{
		ray->stepx = -1;
		ray->sidedist_x = (x - ray->mapx) * ray->deltadist_x;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedist_x = (ray->mapx + 1.0 - x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->stepy = -1;
		ray->sidedist_y = (y - ray->mapy) * ray->deltadist_y;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedist_y = (ray->mapy + 1.0 - y) * ray->deltadist_y;
	}
}

void	calculate_the_ray(t_cub3d *game, t_ray *ray)
{
	int	hit;
	int	limit;

	hit = 0;
	limit = 20000;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		hit = is_wall(game, ray->mapx, ray->mapy, false);
		if (hit == 0 && --limit == 0)
			hit = 1;
		ray->door = (hit == 2);
	}
}

void	cast_ray(t_ray *ray, t_cub3d *game, t_raycasting *var)
{
	double			x;
	double			y;

	x = game->player.x;
	y = game->player.y;
	ray->mapx = (int)game->player.x;
	ray->mapy = (int)game->player.y;
	var->ray_angle = var->start_angle + var->i * var->angle_step;
	var->diff_angle = game->player.angle - var->ray_angle;
	init_ray(ray, var->ray_angle, x, y);
	calculate_the_ray(game, ray);
	if (ray->side == 0)
		var->perp_walldist
			= (ray->mapx - x + (1 - ray->stepx) / 2) / ray->raydir_x;
	else
		var->perp_walldist
			= (ray->mapy - y + (1 - ray->stepy) / 2) / ray->raydir_y;
}

void	fish_eye(t_raycasting *var)
{
	if (var->perp_walldist <= 0)
		var->perp_walldist = 1;
	var->perp_walldist = var->perp_walldist * cos(var->diff_angle);
}

void	cast_all_rays(t_cub3d *game)
{
	t_raycasting	var;
	t_ray			ray;
	t_wall			current_wall;

	var.fov = 66.0 * (M_PI / 180.0);
	var.angle_step = var.fov / WIN_WIDTH;
	var.start_angle = game->player.angle - (var.fov / 2);
	var.i = 0;
	while (var.i < WIN_WIDTH)
	{
		cast_ray(&ray, game, &var);
		fish_eye(&var);
		get_wall_height(&var);
		game->move = var.perp_walldist;
		draw_floor_and_ceiling(game, var.i, var.drawstart, var.drawend);
		draw_wall(game, &var, &current_wall, &ray);
		var.i++;
	}
}
