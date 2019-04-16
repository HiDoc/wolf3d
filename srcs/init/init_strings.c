/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:01:46 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/09 23:29:32 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static SDL_Surface	*ui_create_simple_string(t_font data)
{
	SDL_Surface	*tmp;
	SDL_Surface	*surface;

	if (!(tmp = lt_push(TTF_RenderText_Shaded(
	data.font, data.str, data.color, TRANSPARENT), srf_del)))
		doom_error_exit("Doom_nukem error on TTF_RenderText_Shaded");
	if (!(surface = lt_push(
	SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0), srf_del)))
		doom_error_exit("Doom_nukem error on TTF_RenderText_Shaded");
	lt_release(tmp);
	return (surface);
}

SDL_Surface	*create_scaled_surface(SDL_Surface *surface, t_vtx new_size)
{
	if (!(surface = lt_push(SDL_CreateRGBSurface(0,
	new_size.x, new_size.y, 32, 0xff000000, 0xff0000, 0xff00, 0xff), srf_del)))
		doom_error_exit("Doom_nukem error on SDL_CreateRGBSurface");
	return (surface);
}

static void	set_inv_strings(t_env *env)
{
	int			i;
	t_vtx		new_size;
	SDL_Surface	*tmp;
	const char	*string[DSCRIP_STR_INV] = {
	I_STRING_0, I_STRING_1, I_STRING_2, I_STRING_3, I_STRING_4, I_STRING_5,
	I_STRING_6, I_STRING_7, I_STRING_8, I_STRING_9, I_STRING_10, I_STRING_11};

	i = -1;
	while (++i < DSCRIP_STR_INV)
	{
		tmp = ui_create_simple_string((t_font){WHITE,
		string[i], env->hud.text.text, {0, 0}, 0, -1, -1});
		new_size = (t_vtx){tmp->w / (100 / (W / 50)), tmp->h / (100 / (W / 50))};
		env->hud.text.i_obj_description[i] = create_scaled_surface(env->hud.text.i_obj_description[i], new_size);
		// if (!(env->hud.text.i_obj_description[i] = lt_push(SDL_CreateRGBSurface(0,
		// new_size.x, new_size.y, 32, 0xff000000, 0xff0000, 0xff00, 0xff), srf_del)))
		// 	doom_error_exit("Doom_nukem error on SDL_CreateRGBSurface");
		ui_scaled_copy(tmp, env->hud.text.i_obj_description[i]);
	}
}

static void	set_door_strings(t_env *env)
{
	const char	*string[2] = {STR_DOOR_0, STR_DOOR_1};
	int			i;
	SDL_Surface	*tmp;
	t_vtx		new_size;

	i = -1;
	while (++i < 2)
	{
		tmp = ui_create_simple_string((t_font){WHITE,
		string[i], env->hud.text.text, {0, 0}, 0, -1, -1});
		new_size = (t_vtx){tmp->w / (100 / (W / 40)), tmp->h / (100 / (W / 40))};
		if (!(env->hud.text.doors[i] = lt_push(SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32,
		0xff000000, 0xff0000, 0xff00, 0xff), srf_del)))
			doom_error_exit("Doom_nukem error on SDL_CreateRGBSurface");
		ui_scaled_copy(tmp, env->hud.text.doors[i]);
	}
}

static void	set_pick_strings(t_env *env)
{
	SDL_Surface	*tmp;
	t_vtx		new_size;

	tmp = NULL;
	tmp = ui_create_simple_string((t_font){WHITE,
	PICK_STRING, env->hud.text.text, {0, 0}, 0, -1, -1});
	new_size = (t_vtx){tmp->w / (100 / (W / 40)), tmp->h / (100 / (W / 40))};
	if (!(env->hud.text.pick = lt_push(SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32,
	0xff000000, 0xff0000, 0xff00, 0xff), srf_del)))
		doom_error_exit("Doom_nukem error on SDL_CreateRGBSurface");
	ui_scaled_copy(tmp, env->hud.text.pick);
}

static void	underscore_off_name(char *name, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		name[i] == '_' ? name[i] = ' ' : 0;
}

SDL_Surface **tab_name_objects(t_env *env, int i, t_vtx new_size)
{
	const char	*tab[WORLD_NB_OBJECTS] = {N_HEALTH, N_SHIELD, N_AMMO_M_R,
	N_AMMO_S, N_AMMO_R, N_JETPACK, N_GEM_B, N_GEM_G, N_GEM_R, N_GEM_P, N_MAGNUM,
	N_SHOTGUN, N_RIFLE, N_RPG};
	SDL_Surface	**new;
	SDL_Surface	*tmp;
	char		*name;

	new = ft_memalloc(sizeof(SDL_Surface**) * WORLD_NB_OBJECTS);
	while (++i < WORLD_NB_OBJECTS)
	{
		name = ft_strdup(tab[i]);
		underscore_off_name(name, ft_strlen(name));
		tmp = ui_create_simple_string((t_font){WHITE,
		name, env->hud.text.text, (t_vtx){0, 0}, 0, -1, -1});
		new_size = (t_vtx){tmp->w / (100 / (W / 40)), tmp->h / (100 / (W / 40))};
		if (!(new[i] = lt_push(SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32,
		0xff000000, 0xff0000, 0xff00, 0xff), srf_del)))
			doom_error_exit("Doom_nukem error on SDL_CreateRGBSurface");
		ui_scaled_copy(tmp, new[i]);
		lt_release(name);
	}
	return (new);
}

void		init_strings(t_env *env, int i, int j)
{
	t_vtx		new_size;
	TTF_Font	*font;
	SDL_Surface	*tmp;
	const char      *string[UI_NB_STRING] = {
	STRING_0, STRING_1, STRING_2, STRING_3, STRING_4, STRING_5, STRING_6,
	STRING_7, STRING_8, STRING_9, STRING_10, STRING_11, STRING_12, STRING_13,
	STRING_14, STRING_15, STRING_16, STRING_17, STRING_18, STRING_19, STRING_20,
	STRING_21, STRING_22, STRING_23, STRING_24, STRING_25, STRING_26, STRING_27,
	STRING_28, STRING_29};
	int	size[UI_NB_STR_INV + 1] = {W / 20, W / 34, W / 34, W / 34, W / 60, W / 44, W / 120,
	W / 120, W / 120, W / 120, W / 120, W / 40};

	while (i < UI_NB_STRING)
	{
		font = i <= T_STATS && i >= T_INVENTORY ? env->hud.text.doom : env->hud.text.text;
		tmp = ui_create_simple_string((t_font){WHITE,
		string[i], font, {0, 0}, 0, -1, -1});
		if (i < HUD_NB_STRING)
			new_size = (t_vtx){tmp->w / (100 / size[UI_NB_STR_INV]),
			tmp->h / (100 / size[UI_NB_STR_INV])};
		else
		{
			new_size = (t_vtx){tmp->w / (100 / size[j]), tmp->h / (100 / size[j])};
			j++;
		}
		if (!(env->hud.text.string[i] = lt_push(SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32,
		0xff000000, 0xff0000, 0xff00, 0xff), srf_del)))
			doom_error_exit("Doom_nukem error on SDL_CreateRGBSurface");
		ui_scaled_copy(tmp, env->hud.text.string[i]);
		i++;
	}
	env->hud.text.obj_names = tab_name_objects(env, -1, (t_vtx){0, 0});
	set_inv_strings(env);
	set_pick_strings(env);
	set_door_strings(env);
}
