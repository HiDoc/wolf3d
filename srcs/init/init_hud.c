/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:19:06 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/09 22:25:02 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		init_inv_bg(t_uinv *inventory, SDL_Surface *img)
{
	inventory->bg.sprite = img;
	inventory->bg.rect = (SDL_Rect){0, 0, W, H};
}

static void		init_igems_bloc(t_uinv *inventory, t_container *surfaces)
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

static void		init_icon_bloc(t_uinv *inventory, t_container *surfaces)
{
	int 		i;
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

static void	init_iwpn_bloc(t_hud *hud, t_uinv *inventory, t_container *surfaces)
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
		inventory->wpn[index].cross = (t_minibloc){
		(SDL_Rect){rect.x, rect.y, hud->text.string[CROSS]->w,
		hud->text.string[CROSS]->h}, hud->text.string[CROSS]};
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

static void	init_iobjects_bloc(t_env *env, t_hud *hud, t_uinv *inventory)
{
	int			i;
	SDL_Rect	rect;
	int			interx;
	int			intery;
	SDL_Surface	**img;

	interx = W / 128;
	intery = H / 6.2;
	rect = (SDL_Rect){W / 28, intery, W / 11, W / 11};
	img = hud->text.string;
	i = 0;
	while (i < 6)
	{
		inventory->objects[i].cross = (t_minibloc){
		(SDL_Rect){rect.x + rect.w - img[CROSS]->w, rect.y,
		img[CROSS]->w, img[CROSS]->h}, img[CROSS]};
		inventory->objects[i].use = (t_minibloc){
		(SDL_Rect){rect.x + rect.w - img[USE]->w, rect.y + rect.h - img[USE]->h,
		img[USE]->w, img[USE]->h}, img[USE]};
		inventory->objects[i].bg_empty = env->world.surfaces.hud[BOX_E].sprite;
		inventory->objects[i].bg_fill = env->world.surfaces.hud[BOX_F].sprite;
		inventory->objects[i].rect = rect;
		rect.x = i == 2 ? W / 28 : rect.x + interx + rect.w;
		rect.y = i < 2 ? intery : interx + intery + rect.h;
		i++;
	}
}

static void	init_hp_bloc(t_hud *hud, t_container *surfaces)
{
	int 		i;
	int 		rfaces;
	int 		rbars;
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
	SDL_Surface	**str;

	interx = W / 404;
	rect = (SDL_Rect){W - W / 1.22, H - H  / 8, W / 20, W / 20};
	str = hud->text.string;
	i = 0;
	while (i < 5)
	{
		hud->objects[i].cross = (t_minibloc){
		(SDL_Rect){rect.x + rect.w / 2, rect.y - W / 700,
		str[i + PAD_INDEX]->w, str[i + PAD_INDEX]->h}, str[i + PAD_INDEX]};
		hud->objects[i].use.rect = (SDL_Rect){
		rect.x, rect.y + rect.h - rect.w / 6, rect.w / 6, rect.w / 6};
		hud->objects[i].bg_empty = surfaces->hud[BOX_E].sprite;
		hud->objects[i].bg_fill = surfaces->hud[BOX_F].sprite;
		hud->objects[i].rect = rect;
		rect.x += interx + rect.w;
		i++;
	}
}

void	init_hud(t_env *env)
{
	int	i_tab;
	t_hud	*hud;
	t_uinv	*inv;

	i_tab = 0;
	hud = &env->hud;
	inv = &env->hud.inventory;
    env->hud.is_txt = 0;
	init_inv_bg(inv, env->world.surfaces.hud[0].sprite);
	init_igems_bloc(inv, &env->world.surfaces);
	init_icon_bloc(inv, &env->world.surfaces);
	init_iwpn_bloc(hud, inv, &env->world.surfaces);
	init_iobjects_bloc(env, hud, inv);
	init_hp_bloc(hud, &env->world.surfaces);
	init_hwpn_bloc(hud, &env->world.surfaces);
	init_hobjects_bloc(hud, &env->world.surfaces);
}
