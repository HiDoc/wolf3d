/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:12 by abaille           #+#    #+#             */
/*   Updated: 2019/03/25 00:24:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	*scale_hud_img(SDL_Surface *img, SDL_Rect rect)
{
	int		x;
	int		y;
	t_vtx	scale;
	int		*tab;

	scale.x = fabs((float)img->w / rect.w);
	scale.y = fabs((float)img->h / rect.h);
	if (!(tab = malloc(sizeof(tab) * (img->w * img->h))))
		return (NULL);
	bzero(tab, img->w * img->h);
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

int	init_icon_bloc(t_uinv *inventory, t_container *surfaces)
{
	int 		i;
	int			ref;
	SDL_Rect	rect;
	int			inter;

	inter = W / 8;
	i = ICON_SLOT_1;
	ref = 0;
	rect = (SDL_Rect){W / 24, H - H / 11, W / 21, H / 15.5};
	while (i < FACE_1)
	{
		inventory->icons[ref] = (t_bloc){
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
		NULL, NULL, surfaces->hud[i], rect, ref, 1,
		need_scale(surfaces->hud[i], rect) ? scale_hud_img(surfaces->hud[i], rect) : NULL,
		NULL};
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
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
			NULL, NULL, surfaces->hud[i], rect, rfaces, 0,
			need_scale(surfaces->hud[i], rect) ? scale_hud_img(surfaces->hud[i], rect) : NULL,
			NULL};
			rfaces++;
		}
		else
		{
			hud->bar[rbars] = (t_bloc){
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
			NULL, NULL, surfaces->hud[i], rect, rbars, 0,
			need_scale(surfaces->hud[i], rect) ? scale_hud_img(surfaces->hud[i], rect) : NULL,
			NULL};
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
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
		NULL, NULL, surfaces->hud[i], rect, index, 0,
		need_scale(surfaces->hud[i], rect) ? scale_hud_img(surfaces->hud[i], rect) : NULL,
		NULL};
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
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
		surfaces->hud[i], surfaces->hud[j], NULL, rect, index, 0,
		need_scale(surfaces->hud[i], rect) ? scale_hud_img(surfaces->hud[i], rect)
		: NULL,
		NULL};
		rect.x += rect.w + inter;
		i++;
		j++;
		index++;
	}
	return (1);
}

t_minibloc	fill_minibloc(SDL_Rect brect, SDL_Surface *img, t_ixy size, int pos)
{
	SDL_Rect	rect;
	t_minibloc	new;

	rect = (SDL_Rect){brect.x + brect.w - brect.w / size.x,
	pos, brect.w / size.x, brect.h / size.y};
	new = (t_minibloc) {rect, img,
	need_scale(img, rect)
	? scale_hud_img(img, rect)
	: NULL};
	return (new);
}

int	init_iobjects_bloc(t_env *env, t_uinv *inventory)
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
		fill_minibloc(rect, env->player.hud.text.t_inv[2], (t_ixy){5, 4}, rect.y),
		fill_minibloc(rect, env->player.hud.text.t_inv[3], (t_ixy){5, 5}, rect.y + rect.h - rect.h / 5),
		env->world.surfaces.hud[BOX_E], env->world.surfaces.hud[BOX_F],
		NULL, rect, i, 0,
		need_scale(env->world.surfaces.hud[BOX_E], rect)
		? scale_hud_img(env->world.surfaces.hud[BOX_E], rect) : NULL,
		need_scale(env->world.objects[0].sprite, (SDL_Rect){0, 0, rect.w - rect.w / 10,
		rect.w - rect.w / 10}) ? scale_hud_img(env->world.objects[0].sprite,
		(SDL_Rect){0, 0, rect.w - rect.w / 10, rect.w - rect.w / 10}) : NULL};
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
		hud->objects[i] = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
		surfaces->hud[BOX_E], surfaces->hud[BOX_F],
		NULL, rect, i, 0,
		need_scale(surfaces->hud[BOX_E], rect) ? scale_hud_img(surfaces->hud[BOX_E], rect) : NULL,
		need_scale(env->world.objects[0].sprite, rect) ? scale_hud_img(env->world.objects[0].sprite, rect)
		: NULL};
		rect.x += interx + rect.w;
		i++;
	}
	return (1);
}

int	init_inv_bg(t_uinv *inventory, SDL_Surface *img)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){0, 0, W, H};
	inventory->bg = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
	(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL, NULL},
	NULL, NULL, img, rect, 0, 0,
	need_scale(img, rect) ? scale_hud_img(img, rect) : NULL,
	NULL};
	return (1);
}

int	init_hud_blocs(t_env *env)
{
	return (init_inv_bg(&env->player.hud.inventory, env->world.surfaces.hud[0])
	&& init_icon_bloc(&env->player.hud.inventory, &env->world.surfaces)
	&& init_iwpn_bloc(&env->player.hud.inventory, &env->world.surfaces)
	&& init_iobjects_bloc(env, &env->player.hud.inventory)
	&& init_hp_bloc(&env->player.hud, &env->world.surfaces)
	&& init_hwpn_bloc(&env->player.hud, &env->world.surfaces)
	&& init_hobjects_bloc(env, &env->player.hud, &env->world.surfaces));
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