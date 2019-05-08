/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 20:37:12 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 20:52:28 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_igems_bloc(t_uinv *inventory, t_container *surfaces)
{
	int			i;
	SDL_Rect	rect;
	int			inter;
	int			size;

	inter = W / 132;
	size = W / 17;
	rect = (SDL_Rect){W / 32, H / 1.9, size, size};
	i = 0;
	while (i < WORLD_NB_GEMS)
	{
		inventory->gems[i].bg_empty = surfaces->hud[BOX_E].sprite;
		inventory->gems[i].bg_fill = surfaces->hud[BOX_F].sprite;
		inventory->gems[i].rect = rect;
		rect.x += inter + size;
		i++;
	}
}

void	init_icon_bloc(t_uinv *inventory, t_container *surfaces)
{
	int			i;
	int			ref;
	SDL_Rect	rect;
	int			inter;

	inter = W / 8;
	ref = 0;
	rect = (SDL_Rect){W / 24, H - H / 11, W / 21, H / 15.5};
	i = ICON_SLOT_1;
	while (i < FACE_1)
	{
		inventory->icons[ref].sprite = surfaces->hud[i].sprite;
		inventory->icons[ref].rect = rect;
		rect.x += rect.w + inter;
		ref++;
		i++;
	}
}

void	init_iwpn_bloc(t_uinv *inventory, t_container *surfaces)
{
	int			i;
	int			j;
	int			index;
	SDL_Rect	rect;
	int			inter;

	inter = W / 64;
	rect = (SDL_Rect){W / 32, H / 1.45, W / 10, H / 10};
	i = W_SLOT_1;
	j = INV_PISTOL;
	index = 0;
	while (i < INV_PISTOL && j < HUD_PISTOL)
	{
		inventory->wpn[index].cross.rect = (SDL_Rect){rect.x + rect.w, rect.y,
			rect.w / 6, rect.h / 5};
		inventory->wpn[index].bg_empty = surfaces->hud[i].sprite;
		inventory->wpn[index].bg_fill = surfaces->hud[j].sprite;
		inventory->wpn[index].rect = rect;
		rect.x = i == W_SLOT_1 + 2 ? W / 32 : rect.x + rect.w + inter;
		rect.y = i > W_SLOT_1 + 1 ? inter / 2 + rect.y + rect.h : rect.y;
		i++;
		j++;
		index++;
	}
}

void	init_iobjects_bloc(t_env *env, t_uinv *inventory)
{
	int			i;
	SDL_Rect	rect;
	int			interx;
	int			intery;
	t_bloc		*b;

	interx = W / 128;
	intery = H / 6.2;
	rect = (SDL_Rect){W / 28, intery, W / 11, W / 11};
	i = 0;
	while (i < 6)
	{
		b = &inventory->objects[i];
		b->cross.rect = (SDL_Rect){rect.x + rect.w - rect.w / 4, rect.y,
			rect.w / 4, rect.w / 4};
		b->use.rect = (SDL_Rect){rect.x + rect.w - rect.w / 5,
			rect.y + rect.h - rect.h / 4, rect.w / 5, rect.h / 4};
		b->bg_empty = env->world.surfaces.hud[BOX_E].sprite;
		b->bg_fill = env->world.surfaces.hud[BOX_F].sprite;
		b->rect = rect;
		rect.x = i == 2 ? W / 28 : rect.x + interx + rect.w;
		rect.y = i < 2 ? intery : interx + intery + rect.h;
		i++;
	}
}
