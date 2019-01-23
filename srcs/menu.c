/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:48:54 by jsauron           #+#    #+#             */
/*   Updated: 2019/01/23 17:30:42 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			menu(t_env *env)
{
	if (env->menu.is_active)
	{
		if (env->menu.sub_menu)
			display_sub_menu(env, env->menu.sub_menu);
		else
		{
			put_img(env, env->menu.sprite, 0, 0);
			display_button_menu(env);
		}
	}
	return (0);
}

int			display_sub_menu(t_env *env, int i)
{
	if (i <= env->menu.nb_sub)
		put_img(env, env->menu.sub[i].sprite, 0, 0);
	return (0);
}

int			init_menu_surface(t_env *env)
{
	env->menu.nb_sub = 3;
	if (!(env->menu.sub = (t_menu *)malloc(sizeof(t_menu) * (3))))
		; //print something ?
	env->menu.is_active = 0;
	env->menu.sprite = create_surf("./rsrc/menu/doom_menu_1_vect.png");
	env->menu.sub[0].sprite = create_surf("./rsrc/menu/button_radiation.png");
	env->menu.sub[1].sprite = create_surf("./rsrc/menu/doom_load_game_vect.png");
	return (0);
}

int			select_button_menu(t_env *env, Uint8 keycodes)
{
	if (keycodes == SDL_SCANCODE_RETURN)
	{
		if (env->menu.button == 2)
			env->menu.sub_menu = 1;
		else if (env->menu.button == 3)
			sdl_exit_wolf(env);
	}
	return (0);
}

int			display_button_menu(t_env *env)
{
	if (env->menu.button == 1)
		put_img(env, env->menu.sub[0].sprite, 250, 322);
	else if (env->menu.button == 2)
		put_img(env, env->menu.sub[0].sprite, 250, 400);
	else if (env->menu.button == 3)
		put_img(env, env->menu.sub[0].sprite, 250, 478);
	else if (env->menu.button == 4)
		put_img(env, env->menu.sub[0].sprite, 18, 505);
	else if (env->menu.button == 5)
		put_img(env, env->menu.sub[0].sprite, 528, 505);
	return (0);
}

int			move_button_menu(t_env *env, Uint8 keycodes)
{
	if (env->menu.is_active == 1
			&& (keycodes == SDL_SCANCODE_DOWN || keycodes == SDL_SCANCODE_UP))
	{
		if (keycodes == SDL_SCANCODE_DOWN)
			env->menu.button += 1;
		else
			env->menu.button -= 1;
	}
	if (env->menu.button > 5)
		env->menu.button = 1;
	else if (env->menu.button < 1)
		env->menu.button = 5;
	return (0);
}
