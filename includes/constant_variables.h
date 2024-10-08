/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant_variables.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:03:47 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/23 16:56:52 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANT_VARIABLES_H
# define CONSTANT_VARIABLES_H

# define USAGE "Usage: ./cub3D <file>.cub\n"
# define REDECLARATION "Texture Element declared multiple times\n"
# define INVALID "Invalid element or incorrect formatting\n"
# define INVALID_NUMBER "Invalid number in color\n"
# define INVALID_CHAR "Invalid character in map found\n"
# define NUMBER_EXPECTED "Missing number or non-numeric characters found\n"
# define INCOMPLETE "Incomplete map\n"
# define UNEXPECTED_END "Unexpected content after end of map\n"
# define DUPLICATE_START "Multiple start positions found in map\n"
# define MISSING_START "No start position defined in map\n"
# define NOT_CLOSED "Map not closed, or ' ' in reachable area\n"
# define ONLY_SPACE "Line with nothing but spaces found\n"
# define SPRITES_FAILED "Unable to load sprites\n"

# define MLXINIT "The mlx library initialization failed\n"
# define WINDOWSINIT "The windows initialization failed\n"
# define XPM_ERROR "Error loading xpm image\n"
# define XLM_IMAGE "mlx_new_image function failed\n"
# define IMG_DATA "mlx_get_data_addr function failed\n"
# define TEXTURE "Error: Could not load texture\n"

# define WIN_WIDTH 1050
# define WIN_HEIGHT 600
# define TILE_SIZE 64
# define PLAYER_SIZE 16
# define MOVE_SPEED 8
# define MOVE_CHECK 16

#endif
