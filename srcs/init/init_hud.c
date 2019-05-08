/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:19:06 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 20:52:10 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_inv_bg(t_uinv *inventory, SDL_Surface *img)
{
	inventory->bg.sprite = img;
	inventory->bg.rect = (SDL_Rect){0, 0, W, H};
}

static void	init_hp_bloc(t_hud *hud, t_container *surfaces)
{
	int			i;
	int			rfaces;
	int			rbars;
	SDL_Rect	rect;

	rfaces = 0;
	rbars = 0;
	rect = (SDL_Rect){W / 128, H - H / 2.8, W / 3, H / 4};
	i = FACE_1;
	while (i < W_SLOT_1)
	{
		if (i < HP_BAR_1)
		{
			hud->faces[rfaces].sprite = surfaces->hud[i].sprite;
			hud->faces[rfaces].rect = rect;
			rfaces++;
		}
		else
		{
			hud->bar[rbars].sprite = surfaces->hud[i].sprite;
			hud->bar[rbars].rect = rect;
			rbars++;
		}
		i++;
	}
}

static void	init_hwpn_bloc(t_hud *hud, t_container *surfaces)
{
	int			index;
	int			i;
	SDL_Rect	rect;

	rect = (SDL_Rect){W - W / 6, H / 1.2, W / 10, H / 7};
	i = HUD_PISTOL;
	index = 0;
	while (i <= HUD_W_LAST)
	{
		hud->hud_wpn[index].sprite = surfaces->hud[i].sprite;
		hud->hud_wpn[index].rect = rect;
		i++;
		index++;
	}
}

static void	init_hobjects_bloc(t_hud *hud, t_container *surfaces)
{
	int			i;
	SDL_Rect	rect;
	int			interx;

	interx = W / 404;
	rect = (SDL_Rect){W - W / 1.22, H - H / 8, W / 20, W / 20};
	i = 0;
	while (i < 5)
	{
		hud->objects[i].use.rect = (SDL_Rect){
		rect.x, rect.y + rect.h - rect.w / 6, rect.w / 6, rect.w / 6};
		hud->objects[i].bg_empty = surfaces->hud[BOX_E].sprite;
		hud->objects[i].bg_fill = surfaces->hud[BOX_F].sprite;
		hud->objects[i].rect = rect;
		rect.x += interx + rect.w;
		i++;
	}
}

void		init_hud(t_env *env)
{
	int		i_tab;
	t_hud	*hud;
	t_uinv	*inv;

	i_tab = 0;
	hud = &env->hud;
	inv = &env->hud.inventory;
	env->hud.is_txt = 0;
	init_inv_bg(inv, env->world.surfaces.hud[0].sprite);
	init_igems_bloc(inv, &env->world.surfaces);
	init_icon_bloc(inv, &env->world.surfaces);
	init_iwpn_bloc(inv, &env->world.surfaces);
	init_iobjects_bloc(env, inv);
	init_hp_bloc(hud, &env->world.surfaces);
	init_hwpn_bloc(hud, &env->world.surfaces);
	init_hobjects_bloc(hud, &env->world.surfaces);
}
