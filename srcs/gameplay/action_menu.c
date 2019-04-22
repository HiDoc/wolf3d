/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/04/22 15:48:06 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	action_mainmenu(t_env *e, t_status *s, const Uint8 *k)
{
	scroll_menu(&s->current, k, 0, NB_BLOC_NG);
	if (k[SDL_SCANCODE_RETURN])
	{
		s->current == 0 ? s->on = 0 : 0; //launch cinematik ? s->on = 0; // provisoire
		s->current == 0 ? s->main_menu = 0 : 0;
		s->current == 1 ? s->load_menu = 1 : 0;
		s->current == 2 ? s->options_menu = 1 : 0;
		s->current == 3 ? s->quit = 1 : 0;
		s->load_menu || s->options_menu ? s->current = 0 : 0;
		!s->main_menu ? set_msc_menu(e, s) : 0;
	}
	menu_btn_sound(e, k);
}

void	action_ingame_menu(t_env *e, t_status *s, const Uint8 *k)
{
	scroll_menu(&s->current, k, 0, NB_BLOC_IG - 1);
	if (k[SDL_SCANCODE_LEFT] && s->current == 0)
		s->current = 3;
	else if (k[SDL_SCANCODE_RIGHT] && s->current == 3)
		s->current = 0;
	else if ((k[SDL_SCANCODE_RETURN]))
	{
		s->current == 0 ? create_save(e, s) : 0; //	save game
		s->current == 1 ? s->options_menu = 1 : 0;
		s->current == 2 ? s->main_menu = 1 : 0; // save en mm tps
		s->current == 3 ? s->on = !s->on : 0;
		!s->options_menu && s->current ? s->ingame_menu = 0 : 0;
		if (!s->ingame_menu && !s->main_menu)
			set_msc_menu(e, s);
		s->current = 0;
	}
	menu_btn_sound(e, k);
}

void	action_loadmenu(t_env *e, t_status *s, const Uint8 *k)
{
	int		i;
	t_bloc	*b;

	i = 0;
	b = e->menu.save_game;
	if (s->nb_save && s->nb_save < 6)
		scroll_menu(&s->current, k, 0, s->nb_save);
	else
	{
		if (k[SDL_SCANCODE_DOWN] && s->current >= s->end && s->end < s->nb_save)
		{
			s->start++;
			s->end++;
		}
		if (k[SDL_SCANCODE_UP] && s->current <= s->start && s->start > 1)
		{
			s->start--;
			s->end--;
		}
	}
	if (k[SDL_SCANCODE_RETURN])
	{
		s->current == 0 ? s->load_menu = 0 : 0;
		while (b && ++i < s->nb_save && s->current != 0)
		{
			b = b->next;
		}
	}
}

void	action_optionmenu(t_env *e, t_status *s, const Uint8 *k)
{
	if ((k[SDL_SCANCODE_UP] || k[SDL_SCANCODE_DOWN]) && !s->key_change)
		scroll_menu(&s->current, k, 0, NB_OPT_MENU);
	if (k[SDL_SCANCODE_LEFT] && !s->key_change)
	{
		s->current == 0 ? s->current = NB_OPT_KEY : 0;
		s->current > I_OINVENTR && s->current != NB_OPT_KEY
		? s->current -= I_OINVENTR : 0;
	}
	else if (k[SDL_SCANCODE_RIGHT] && !s->key_change)
	{
		s->current == NB_OPT_KEY ? s->current = 0 : 0;
		s->current < I_OPICKOPN && s->current
		? s->current += I_OINVENTR : 0;
	}
	else if ((k[SDL_SCANCODE_RETURN])
		&& !s->key_change && (s->current == NB_OPT_KEY
		|| s->current == NB_OPT_KEY + 1))
	{
		s->current == NB_OPT_KEY ? s->options_menu = 0 : key_binding(&e->engine);
		s->current = 0;
	}
	else
		change_option(e, s, k, &e->engine.keys[s->current]);
	menu_btn_sound(e, k);
}
