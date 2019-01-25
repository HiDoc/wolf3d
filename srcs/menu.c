/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:48:54 by jsauron           #+#    #+#             */
/*   Updated: 2019/01/25 12:40:56 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			menu(t_env *env)
{
	if (env->menu.is_active)
	{
		if (env->menu.sub_menu)
			display_sub_menu(env, env->menu.sub_menu);
		else if (env->menu.is_active == 1)
		{
			put_img(env, env->menu.sprite, 0, 0);
			display_button_menu(env);
		}
		 if (env->menu.is_active == 2 && env->menu.sub_menu == 2)
			display_button_menu(env);
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
	env->menu.nb_sub = 4;
	if (!(env->menu.sub = (t_menu *)malloc(sizeof(t_menu) * (env->menu.nb_sub))))
		; //print something ?
	env->menu.is_active = 1;
	env->menu.sprite = create_surf("./rsrc/menu/doom_menu_1_vect.png");
	env->menu.sub[0].sprite = create_surf("./rsrc/menu/buttonF.png");
	env->menu.sub[1].sprite = create_surf("./rsrc/menu/doom_load_game_vect.png");
	env->menu.sub[2].sprite = create_surf("./rsrc/menu/doom_menu_2_vect.png");
	env->menu.sub[3].sprite = create_surf("./rsrc/menu/doom_save_game_vect.png");
	return (0);
}

int			select_button_menu(t_env *env, Uint8 keycode)
{
	if (env->menu.is_active == 1)
		select_button_menu_1(env, keycode);
	else if (env->menu.is_active == 2)
		select_button_menu_2(env, keycode);
	return (0);
}

int			select_button_menu_1(t_env *env, Uint8 keycode)
{
	if (keycode == SDL_SCANCODE_RETURN)
	{
		if (env->menu.button == 0)
			env->menu.is_active = 0;
		else if (env->menu.button == 1)
			env->menu.sub_menu = 1;
		else if (env->menu.button == 2)
			sdl_exit_wolf(env);
	}
	return (0);
}

int			select_button_menu_2(t_env *env, Uint8 keycode)
{
	if (keycode == SDL_SCANCODE_RETURN)
	{
		if (env->menu.button == 0)
			env->menu.sub_menu = 3;
		if (env->menu.button == 1)
			sdl_exit_wolf(env);
	}
	return (0);
}

int			display_button_menu(t_env *env)
{
	if (env->menu.button == 0)
		put_img(env, env->menu.sub[0].sprite, 250, 322);
	else if (env->menu.button == 1)
		put_img(env, env->menu.sub[0].sprite, 250, 400);
	else if (env->menu.button == 2)
		put_img(env, env->menu.sub[0].sprite, 250, 478);
	else if (env->menu.button == 3)
		put_img(env, env->menu.sub[0].sprite, 18, 505);
	else if (env->menu.button == 4)
		put_img(env, env->menu.sub[0].sprite, 528, 505);
	return (0);
}

int			move_button_menu(t_env *env, Uint8 keycode)
{
	if (env->menu.is_active
			&& (keycode == SDL_SCANCODE_DOWN || keycode == SDL_SCANCODE_UP))
	{
		if (keycode == SDL_SCANCODE_DOWN)
			env->menu.button += 1;
		else
			env->menu.button -= 1;
	}
	if (env->menu.is_active == 1)
	{
		if (env->menu.button > 4)
			env->menu.button = 0;
		else if (env->menu.button < 0)
			env->menu.button = 4;
	}
	else if (env->menu.is_active == 2)
	{
		if (env->menu.button > 2)
			env->menu.button = 0;
		else if (env->menu.button < 0)
			env->menu.button = 2;
	}
	return (0);
}
