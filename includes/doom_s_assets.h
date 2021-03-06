/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_assets.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:42:58 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/29 17:05:36 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_ASSETS_H
# define DOOM_S_ASSETS_H

typedef struct s_surface	t_surface;
typedef struct s_drawline	t_drawline;

struct						s_surface
{
	SDL_Surface	*sprite;
	int			health;
	int			shield;
	int			height;
	int			damage;
	int			width;
	double		angle;
};

/*
** Container to draw a vertical line inside an SDL_Surface pixels array.
*/
struct						s_drawline
{
	void		*container;
	int			from;
	int			to;
	int			bottom;
	int			middle;
	int			top;
};
#endif
