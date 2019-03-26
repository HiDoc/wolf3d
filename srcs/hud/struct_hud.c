/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:12 by abaille           #+#    #+#             */
/*   Updated: 2019/03/26 12:09:29 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	*scale_hud_img(SDL_Surface *img, SDL_Rect rect, int *tab)
{
	int		x;
	int		y;
	t_vtx	scale;

	scale.x = fabs((float)img->w / rect.w);
	scale.y = fabs((float)img->h / rect.h);
	bzero(tab, 20);
	x = 0;
	while (x < rect.w)
	{
		y = 0;
		while (y < rect.h)
		{
			tab[img->w * (int)(y * scale.y) + (int)(x * scale.x)] = 1;
			y++;
		}
		x++;
	}
	return (tab);
}

int	need_scale(SDL_Surface *img, SDL_Rect rect)
{
	return (img->w > rect.w || img->h > rect.h);
}

int	scale_tab(SDL_Surface *img, SDL_Rect rect, int *tab)
{
	tab = need_scale(img, rect) ? scale_hud_img(img, rect, tab) : NULL;
	return (1);
}


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
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
		NULL, NULL, surfaces->hud[i], rect, ref, 1,
		surfaces->hud[i]->w / rect.w, 0};
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
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
			NULL, NULL, surfaces->hud[i], rect, rfaces, 0,
			surfaces->hud[i]->w / rect.w, 0};
			rfaces++;
		}
		else
		{
			hud->bar[rbars] = (t_bloc){
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
			NULL, NULL, surfaces->hud[i], rect, rbars, 0,
			surfaces->hud[i]->w / rect.w, 0};
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

	rect = (SDL_Rect){W - W / 6, H / 1.2, W / 20, H / 14};
	i = HUD_PISTOL;
	index = 0;
	while (i <= HUD_RIFLE)
	{
		hud->hud_wpn[index] = (t_bloc){
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
		NULL, NULL, surfaces->hud[i], rect, index, 0,
		surfaces->hud[i]->w / rect.w, 0};
		i++;
		index++;
	}
	return (1);
}

int	init_iwpn_bloc(t_uinv *inventory, t_container *surfaces)
{
	int			i;
	int			j;
	int			index;
	SDL_Rect	rect;
	int			inter;

	inter = W / 64;
	rect = (SDL_Rect){W / 32, H - H / 3, W / 7, H / 7};
	i = W_SLOT_1;
	j = INV_PISTOL;
	index = 0;
	while (i < INV_PISTOL && j < HUD_PISTOL)
	{
		inventory->wpn[index] = (t_bloc){
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
		surfaces->hud[i], surfaces->hud[j], NULL, rect, index, 0,
		surfaces->hud[i]->w / rect.w, 0};
		rect.x += rect.w + inter;
		i++;
		j++;
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

	new = (t_minibloc) {rect, img, img->w / rect.w};
	return (new);
}


int	init_iobjects_bloc(t_env *env, t_hud *hud, t_uinv *inventory)
{
	int			i;
	SDL_Rect	rect;
	int			interx;
	int			intery;

	interx = W / 128;
	intery = H / 6;
	rect = (SDL_Rect){W / 28, intery, W / 8, W / 8};
	i = 0;
	while (i < 6)
	{
		inventory->objects[i] = (t_bloc){
		fill_minibloc(rect, hud->text.t_inv[2], (t_vctr){5, 4, rect.y}),
		fill_minibloc(rect, hud->text.t_inv[3], (t_vctr){4, 4, rect.y + rect.h - rect.h / 4}),
		env->world.surfaces.hud[BOX_E], env->world.surfaces.hud[BOX_F],
		NULL, rect, i, 0, env->world.surfaces.hud[BOX_E]->w / rect.w, env->world.objects[0].sprite->w / rect.w};
		rect.x = i == 2 ? W / 28 : rect.x + interx + rect.w;
		rect.y = i < 2 ? intery : interx + intery + rect.h;
		i++;
	}
	return (1);
}

int	init_hobjects_bloc(t_env *env, t_hud *hud, t_container *surfaces)
{
	int			i;
	SDL_Rect	rect;
	int			interx;

	interx = W / 404;
	rect = (SDL_Rect){W - W / 1.27, H - H  / 8, W / 20, W / 20};
	i = 0;
	while (i < 4)
	{
		hud->objects[i] = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
		surfaces->hud[BOX_E], surfaces->hud[BOX_F],
		NULL, rect, i, 0, surfaces->hud[BOX_E]->w / rect.w, env->world.objects[0].sprite->w / rect.w};
		rect.x += interx + rect.w;
		i++;
	}
	return (1);
}

int	init_inv_bg(t_uinv *inventory, SDL_Surface *img)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){0, 0, W, H};
	inventory->bg = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, 0},
	(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, img->w / rect.w},
	NULL, NULL, img, rect, 0, 0, 0, 0};
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
	return (init_inv_bg(inv, env->world.surfaces.hud[0])
	&& init_icon_bloc(inv, &env->world.surfaces)
	&& init_iwpn_bloc(inv, &env->world.surfaces)
	&& init_iobjects_bloc(env, hud, inv)
	&& init_hp_bloc(hud, &env->world.surfaces)
	&& init_hwpn_bloc(hud, &env->world.surfaces)
	&& init_hobjects_bloc(env, hud, &env->world.surfaces));
}

int init_hud_container(t_env *env)
{
	int	i;

	i = 0;
	while (i < NB_HUD_OBJ)
	{
		if (!(env->world.surfaces.hud[i] = ui_img("hud/", i)))
			return (0);
		i++;
	}
	init_hud_blocs(env);
	return (1);
}