/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/04/18 21:53:19 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	exit_menu(t_env *e, t_status *s, int p)
{
	if (!p)
	{
		set_msc_menu(e, s);
		if ((SDL_SetRelativeMouseMode(SDL_TRUE)) < 0)
			doom_error_exit("Doom_nukem error on SDL_SetRelativeMouseMode");
	}
}

void	action_mainmenu(t_env *e, t_status *s, const Uint8 *k)
{
	scroll_menu(&s->current, k, 0, NB_BLOC_NG);
	if (k[SDL_SCANCODE_RETURN] || s->click)
	{
		s->current == 0 ? s->on = 0 : 0; //launch cinematik ? s->on = 0; // provisoire
		s->current == 1 ? s->load_menu = 1 : 0;
		s->current == 2 ? s->options_menu = 1 : 0;
		s->current == 3 ? s->quit = 1 : 0;
		s->current == 0 ? s->main_menu = 0 : 0;
		s->load_menu || s->options_menu ? s->current = 0 : 0;
		s->click = 0;
		exit_menu(e, s, s->main_menu);
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
	else if ((k[SDL_SCANCODE_RETURN] || s->click))
	{
		s->current == 0 ? s->nb_save++ : 0; //	save game
		s->current == 1 ? s->options_menu = 1 : 0;
		s->current == 2 ? s->main_menu = 1 : 0; // save en mm tps
		s->current == 3 ? s->on = !s->on : 0;
		!s->options_menu ? s->ingame_menu = 0 : 0;
		s->current = 0;
		s->click = 0;
		exit_menu(e, s, s->ingame_menu);
	}
	menu_btn_sound(e, k);
}

void	action_loadmenu(t_env *e, t_status *s, const Uint8 *k)
{
	int		i;
	t_bloc	*b;

	i = 0;
	b = e->menu.games_ldmenu;
	if (s->nb_save)
		scroll_menu(&s->current, k, 0, s->nb_save);
	if (k[SDL_SCANCODE_RETURN] || s->click)
	{
		s->current == 0 ? s->load_menu = 0 : 0;
		s->current == 0 ? s->click = 0 : 0;
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
	else if ((k[SDL_SCANCODE_RETURN] || s->click)
		&& !s->key_change && s->current == NB_OPT_KEY)
	{
		s->options_menu = 0;
		s->current = 0;
		s->click = 0;
	}
	else
		change_option(e, s, k, &e->engine.keys[s->current]);
	menu_btn_sound(e, k);
}


void	action_menu(t_env *e)
{
	t_menu	*m;
	int		x;
	int		y;
	int		i;

	SDL_GetMouseState(&x, &y);
	m = &e->menu;
	if (m->status.ingame_menu && !m->status.options_menu)
		(i = new_btn_current(m->ingame_menu, x, y, NB_BLOC_IG)) > -1
		? m->status.current = i : 0;
	if (m->status.main_menu && !m->status.ingame_menu
	&& !m->status.options_menu && !m->status.load_menu)
		(i = new_btn_current(m->main_menu, x, y, NB_BLOC_NG)) > -1
		? m->status.current = i : 0;
	if (m->status.options_menu && !m->status.key_change)
		(i = new_btn_current(m->options_menu, x, y, NB_OPT_MENU)) > -1
		? m->status.current = i : 0;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		i > -1 ? m->status.click = 1 : 0;
}