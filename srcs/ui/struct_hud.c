/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:12 by abaille           #+#    #+#             */
/*   Updated: 2019/03/23 20:32:07 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// int init_hud_objects(t_hud *hud, char *res)
// {
//     int i;

//     i = 0;
//     while (i < 6)
//     {
//         if (!(hud->objects[i] = ui_img(res, "hud/", "objects/", i)))
//             return (0);
//         hud->shortcut[i] = NULL;
//         i++;
//     }
//     return (1);
// }

// int init_hud_faces(t_hud *hud, char *res)
// {
//     int i;

//     i = 0;
//     while (i < 4)
//     {
//         if (!(hud->faces[i] = ui_img(res, "hud/", "faces/", i)))
//             return (0);
//         i++;
//     }
//     return (1);
// }

// int init_hud_wpn(t_hud *hud, char *res)
// {
//     int i;

//     i = 0;
//     while (i < 3)
//     {
//         if (!(hud->hud_wpn[i] = ui_img(res, "hud/", "wpn/", i)))
//             return (0);
//         i++;
//     }
//     return (1);
// }

// int init_hud_barhp(t_hud *hud, char *res)
// {
//     if ((hud->bar[0] = ui_img(res, "hud/", "hpbars/", 0))
//     && (hud->bar[1] = ui_img(res, "hud/", "hpbars/", 1)))
//         return (1);
//     return (0);
// }

// int init_hud(t_env *env, char *res)
// {
//     if (!(env->player.hud.empty_b = ui_img(res, "hud/", "box/", 0)))
//         return (0);
//     return (init_hud_faces(&env->player.hud, res)
//     && init_hud_barhp(&env->player.hud, res)
//     && init_hud_objects(&env->player.hud, res)
//     && init_hud_wpn(&env->player.hud, res));
// }

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
		inventory->icons[ref] = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL}, NULL, NULL, surfaces->hud[i], rect, ref, 1};
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
			hud->faces[rfaces] = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL}, NULL, NULL, surfaces->hud[i],
			rect, rfaces, 0};
			rfaces++;
		}
		else
		{
			hud->bar[rbars] = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
			(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL}, NULL, NULL, surfaces->hud[i],
			rect, rbars, 0};
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
		hud->hud_wpn[index] = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL}, NULL, NULL,
		surfaces->hud[i], rect, index, 0};
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
		inventory->wpn[index] = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		surfaces->hud[i], surfaces->hud[j], NULL,
		rect, index, 0};
		rect.x += rect.w + inter;
		i++;
		j++;
		index++;
	}
	return (1);
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
		inventory->objects[i] = (t_bloc){(t_minibloc)
		{(SDL_Rect){rect.x + rect.w / 5, rect.y, rect.w / 5, rect.w / 5},
		env->player.hud.text.t_inv[0]},(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		env->world.surfaces.hud[BOX_E], env->world.surfaces.hud[BOX_F],
		NULL, rect, i, 0};
		rect.x = i == 2 ? W / 28 : rect.x + interx + rect.w;
		rect.y = i < 2 ? intery : interx + intery + rect.w;
		i++;
	}
	return (1);
}

int	init_hobjects_bloc(t_hud *hud, t_container *surfaces)
{
	int			i;
	SDL_Rect	rect;
	int			interx;

	interx = W / 128;
	rect = (SDL_Rect){W - W / 1.27, H - H  / 8, W / 40, W / 40};
	i = 0;
	while (i < 4)
	{
		hud->objects[i] = (t_bloc){(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		(t_minibloc){(SDL_Rect){0, 0, 0, 0}, NULL},
		surfaces->hud[BOX_E], surfaces->hud[BOX_F],
		NULL, rect, i, 0};
		rect.x += interx + rect.w;
		i++;
	}
	return (1);
}

int	init_hud_blocs(t_env *env)
{
	return (init_icon_bloc(&env->player.hud.inventory, &env->world.surfaces)
	&& init_iwpn_bloc(&env->player.hud.inventory, &env->world.surfaces)
	&& init_iobjects_bloc(env, &env->player.hud.inventory)
	&& init_hp_bloc(&env->player.hud, &env->world.surfaces)
	&& init_hwpn_bloc(&env->player.hud, &env->world.surfaces)
	&& init_hobjects_bloc(&env->player.hud, &env->world.surfaces));
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