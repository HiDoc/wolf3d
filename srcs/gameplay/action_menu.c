/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/05/04 02:04:06 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		load_world_data(int index, t_env *env)
{
	int     fd;
	char    *line;
	int     i;

	line = 0;
	if ((fd = open("worlds", O_RDONLY)) == -1)
		doom_error_exit("Doom_nukem: fd error in load_world_data");
	i = -1;
	while ((get_next_line(fd, &line)) > 0 && i < index)
	{
		(line[0] == '#') ? i++ : 0;
		lt_release(line);
	}
	env->nb_levels = ft_atoi(line);
	env->levels = ft_memalloc(sizeof(t_level *) * (env->nb_levels + 1));
	i = 0;
	while (i < env->nb_levels)
	{
		env->levels[i] = ft_memalloc(sizeof(t_level));
		if ((get_next_line(fd, &line)) < 0)
			doom_error_exit("Doom_nukem: out of memory in load_world_data");
		env->levels[i]->index = ft_atoi(line);
		lt_release(line);

		if ((get_next_line(fd, &line)) < 0)
			doom_error_exit("Doom_nukem: out of memory in load_world_data");
		env->levels[i]->text_start = ft_strdup(line);
		lt_release(line);

		if ((get_next_line(fd, &line)) < 0)
			doom_error_exit("Doom_nukem: out of memory in load_world_data");
		env->levels[i]->text_end = ft_strdup(line);
		lt_release(line);
		i++;
	}
	close(fd);
}

void	action_mainmenu(t_env *e, t_status *s, const Uint8 *k)
{
	scroll_menu(&s->cur, k, 0, NB_BL_NG);
	if (k[SDL_SCANCODE_RETURN])
	{
		s->cur == 0 ? s->new_game = 1 : 0;
		s->cur == 1 ? s->load_menu = 1 : 0;
		s->cur == 2 ? s->options_menu = 1 : 0;
		s->cur == 3 ? s->quit = 1 : 0;
		s->new_game || s->load_menu || s->options_menu ? s->cur = 0 : 0;
	}
	menu_btn_sound(e, k);
}

void	action_newgame_menu(t_env *e, t_status *s, const Uint8 *k)
{
	if (e->nb_games)
		scroll_menu(&s->cur, k, 0, e->nb_games);
	if (k[SDL_SCANCODE_LEFT] && s->cur == 0)
		s->cur = e->nb_games;
	if (k[SDL_SCANCODE_RIGHT] && s->cur == e->nb_games)
		s->cur = 0;
	if ((k[SDL_SCANCODE_RETURN]))
	{
		if (s->cur < e->nb_games)
		{
			load_world_data(s->cur, e);
			s->inter = 1;
			s->on = 0;
			s->main_menu = 0;
			e->curr_lvl = 0;
			e->levels[s->cur]->tplay = SDL_GetTicks();
		}
		s->new_game = 0;
		s->cur = 0;
		!s->main_menu ? set_msc_menu(e, s) : 0;
	}
	menu_btn_sound(e, k);
}

void	action_ingame_menu(t_env *e, t_status *s, const Uint8 *k)
{
	Uint32	*t;

	scroll_menu(&s->cur, k, 0, NB_BLOC_IG - 1);
	if (k[SDL_SCANCODE_LEFT] && s->cur == 0)
		s->cur = 3;
	else if (k[SDL_SCANCODE_RIGHT] && s->cur == 3)
		s->cur = 0;
	else if ((k[SDL_SCANCODE_RETURN]))
	{
		s->cur == 0 ? create_save(e, s) : 0;
		s->cur == 1 ? s->options_menu = 1 : 0;
		s->cur == 2 ? s->main_menu = 1 : 0;
		s->cur == 3 ? s->on = !s->on : 0;
		!s->options_menu && s->cur ? s->ingame = 0 : 0;
		if (!s->ingame && !s->main_menu)
			set_msc_menu(e, s);
		s->cur = 0;
		t = &e->levels[e->curr_lvl]->tplay;
		s->main_menu ? *t = SDL_GetTicks() - *t : 0;
	}
	menu_btn_sound(e, k);
}

void	action_loadmenu(t_env *e, t_status *s, const Uint8 *k)
{
	int		i;
	t_bloc	*b;

	i = 0;
	b = e->menu.save;
	if (s->nb_save && s->nb_save < 6)
		scroll_menu(&s->cur, k, 0, s->nb_save);
	else if (s->nb_save)
		long_scroll_menu(s, k);
	if (k[SDL_SCANCODE_RETURN])
	{
		s->cur == 0 ? s->load_menu = 0 : 0;
		while (b && ++i < s->nb_save && s->cur != 0)
		{
			if (i == s->cur)
				//go select save
			b = b->next;
		}
	}
}

void	action_optionmenu(t_env *e, t_status *s, const Uint8 *k)
{
	if ((k[SDL_SCANCODE_UP] || k[SDL_SCANCODE_DOWN]) && !s->key_change)
		scroll_menu(&s->cur, k, 0, NB_OPT_MENU);
	if (k[SDL_SCANCODE_LEFT] && !s->key_change)
	{
		s->cur == 0 ? s->cur = NB_OPT_KEY : 0;
		s->cur > I_OINVENTR && s->cur != NB_OPT_KEY
		? s->cur -= I_OINVENTR : 0;
	}
	else if (k[SDL_SCANCODE_RIGHT] && !s->key_change)
	{
		(s->cur == NB_OPT_KEY) ? s->cur = 0 : 0;
		(s->cur < I_OPICKOPN) && s->cur ? s->cur += I_OINVENTR : 0;
	}
	else if ((k[SDL_SCANCODE_RETURN]) && !s->key_change
		&& (s->cur == NB_OPT_KEY || s->cur == NB_OPT_KEY + 1))
	{
		s->cur == NB_OPT_KEY ? s->options_menu = 0 : key_binding(&e->engine);
		s->cur = 0;
	}
	else
		change_option(e, s, k, &e->engine.keys[s->cur]);
	menu_btn_sound(e, k);
}
