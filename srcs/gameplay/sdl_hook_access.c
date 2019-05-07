/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:28:52 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 19:23:29 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		god_mod(t_env *env)
{
	if (env->god_mod)
	{
		env->menu.status.on = 0;
		env->menu.status.home = 0;
		env->menu.status.sound = 0;
		env->player.actions.is_invisible = 1;
	}
	return (1);
}

void	access_menu(t_env *e, t_status *s, int which)
{
	if (which)
	{
		create_save_image(e);
		e->menu.status.on = 1;
		e->menu.status.ingame = 1;
		set_msc_menu(e, &e->menu.status);
		SDL_Delay(300);
	}
	else
	{
		if (s->options_menu || s->load_menu || s->new_game)
		{
			s->key_change = 0;
			s->options_menu = 0;
			s->load_menu = 0;
			s->new_game = 0;
		}
		else if (!s->main_menu)
		{
			s->on = 0;
			s->ingame = 0;
			set_msc_menu(e, s);
			SDL_Delay(300);
		}
		s->cur = 0;
	}
}

void	access_inventory(t_env *e)
{
	e->hud.inventory.is_active = !e->hud.inventory.is_active;
	SDL_Delay(300);
	if ((SDL_SetRelativeMouseMode(SDL_FALSE)) < 0)
		doom_error_exit("Doom_nukem error on SDL_SetRelativeMouseMode");
}
