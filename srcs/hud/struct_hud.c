/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:12 by abaille           #+#    #+#             */
/*   Updated: 2019/04/05 18:05:38 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	init_icon_bloc(t_uinv *inventory, t_container *surfaces)
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
		inventory->icons[ref] = (t_bloc){
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		NULL, NULL, surfaces->hud[i].sprite, rect, ref, 1,
		(t_edge){{0, 0}, {0, 0}}};
		rect.x += rect.w + inter;
		i++;
		ref++;
	}
	return (1);
}

int	init_hp_bloc(t_hud *hud, t_container *surfaces)
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
			hud->faces[rfaces] = (t_bloc){
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			NULL, NULL, surfaces->hud[i].sprite, rect, rfaces, 0,
			(t_edge){{0, 0}, {0, 0}}};
			rfaces++;
		}
		else
		{
			hud->bar[rbars] = (t_bloc){
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			NULL, NULL, surfaces->hud[i].sprite, rect, rbars, 0,
			(t_edge){{0, 0}, {0, 0}}};
			rbars++;
		}
		i++;
	}
	return (1);
}

int	init_hwpn_bloc(t_hud *hud, t_container *surfaces)
{
	int			index;
	int			i;
	SDL_Rect	rect;

	rect = (SDL_Rect){W - W / 6, H / 1.2, W / 10, H / 7};
	i = HUD_PISTOL;
	index = 0;
	while (i <= HUD_W_LAST)
	{
		hud->hud_wpn[index] = (t_bloc){
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		NULL, NULL, surfaces->hud[i].sprite, rect, index, 0,
		(t_edge){{0, 0}, {0, 0}}};
		i++;
		index++;
	}
	return (1);
}

t_minibloc	fill_minibloc(SDL_Rect brect, SDL_Surface *img, t_vctr size)
{
	SDL_Rect	rect;
	t_minibloc	new;

	rect = (SDL_Rect){brect.x + brect.w - brect.w / size.x,
	size.z, brect.w / size.x, brect.h / size.y};

	new = (t_minibloc) {rect, img};
	return (new);
}

int	init_iwpn_bloc(t_hud *hud, t_uinv *inventory, t_container *surfaces)
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
		inventory->wpn[index] = (t_bloc){
		(t_minibloc){(SDL_Rect){rect.x, rect.y, rect.w / 6, rect.w / 6},
		hud->text.t_inv[2]}, (t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		surfaces->hud[i].sprite, surfaces->hud[j].sprite, NULL,
		rect, index, 0, (t_edge){{0, 0}, {0, 0}}};
		rect.x = i == W_SLOT_1 + 2 ? W / 32 : rect.x + rect.w + inter;
		rect.y = i > W_SLOT_1 + 1 ? inter / 2 + rect.y + rect.h : rect.y;
		i++;
		j++;
		index++;
	}
	return (1);
}

int	init_iobjects_bloc(t_env *env, t_hud *hud, t_uinv *inventory)
{
	int			i;
	SDL_Rect	rect;
	int			interx;
	int			intery;

	interx = W / 128;
	intery = H / 6.2;
	rect = (SDL_Rect){W / 28, intery, W / 11, W / 11};
	i = 0;
	while (i < 6)
	{
		inventory->objects[i] = (t_bloc){
		fill_minibloc(rect, hud->text.t_inv[2], (t_vctr){6, 5, rect.y}),
		fill_minibloc(rect, hud->text.t_inv[3],
		(t_vctr){4, 5, rect.y + rect.h - rect.h / 5}),
		env->world.surfaces.hud[BOX_E].sprite,
		env->world.surfaces.hud[BOX_F].sprite,
		NULL, rect, i, 0, (t_edge){{0, 0}, {0, 0}}};
		rect.x = i == 2 ? W / 28 : rect.x + interx + rect.w;
		rect.y = i < 2 ? intery : interx + intery + rect.h;
		i++;
	}
	return (1);
}

int	init_hobjects_bloc(t_hud *hud, t_container *surfaces)
{
	int			i;
	SDL_Rect	rect;
	int			interx;

	interx = W / 404;
	rect = (SDL_Rect){W - W / 1.22, H - H  / 8, W / 20, W / 20};
	i = 0;
	while (i < 5)
	{
		hud->objects[i] = (t_bloc){(t_minibloc)
		{(SDL_Rect){rect.x + rect.w / 2, rect.y - W / 700,
		rect.w / 6, rect.w / 6}, hud->text.t_inv[i + 6]},
		(t_minibloc){(SDL_Rect){rect.x,
		rect.y + rect.h - rect.w / 6, rect.w / 6, rect.w / 6}, NULL},
		surfaces->hud[BOX_E].sprite, surfaces->hud[BOX_F].sprite,
		NULL, rect, i, 0, (t_edge){{0, 0}, {0, 0}}};
		rect.x += interx + rect.w;
		i++;
	}
	return (1);
}

int	init_inv_bg(t_uinv *inventory, SDL_Surface *img)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){0, 0, W, H};
	inventory->bg = (t_bloc){{{0, 0, 0, 0}, NULL},
	{{0, 0, 0, 0}, NULL},
	NULL, NULL, img, rect, 0, 0, {{0, 0}, {0, 0}}};
	return (1);
}

int	init_igems_bloc(t_uinv *inventory, t_container *surfaces)
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
		inventory->gems[i] = (t_bloc){(t_minibloc)
		{(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		surfaces->hud[BOX_E].sprite, surfaces->hud[BOX_F].sprite,
		NULL, rect, i, 0, (t_edge){{0, 0}, {0, 0}}};
		rect.x += inter + size;
		i++;
	}
	return (1);
}

int	init_hud_blocs(t_env *env)
{
	int	i_tab;
	t_hud	*hud;
	t_uinv	*inv;

	i_tab = 0;
	hud = &env->hud;
	inv = &env->hud.inventory;
    env->hud.is_txt = 0;
	return (init_inv_bg(inv, env->world.surfaces.hud[0].sprite)
	&& init_igems_bloc(inv, &env->world.surfaces)
	&& init_icon_bloc(inv, &env->world.surfaces)
	&& init_iwpn_bloc(hud, inv, &env->world.surfaces)
	&& init_iobjects_bloc(env, hud, inv)
	&& init_hp_bloc(hud, &env->world.surfaces)
	&& init_hwpn_bloc(hud, &env->world.surfaces)
	&& init_hobjects_bloc(hud, &env->world.surfaces));
}
