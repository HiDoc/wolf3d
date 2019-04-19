/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_menu_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:12:44 by abaille           #+#    #+#             */
/*   Updated: 2019/04/19 14:37:24 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	scroll_menu(int *cur, const Uint8 *k, int start, int limit)
{
	*cur += k[SDL_SCANCODE_DOWN] ? 1 : 0;
	*cur -= k[SDL_SCANCODE_UP] ? 1 : 0;
	*cur < start ? *cur = limit - 1 : 0;
	*cur == limit && (k[SDL_SCANCODE_DOWN] || k[SDL_SCANCODE_UP])
		? *cur = start : 0;
}

int		check_doublon(t_status *s, int scan, int *ktab)
{
	int	i;

	i = 0;
	if (scan < 0)
	{
		s->key_change = 0;
		return (0);
	}
	while (++i < NB_OPT_KEY)
	{
		if (ktab[i] == scan && i != s->current)
		{
			s->key_change = 0;
			return (0);
		}
	}
	return (1);
}

void	change_option(t_env *e, t_status *s, const Uint8 *k, int *key)
{
	if (!k[SDL_SCANCODE_RETURN] && !k[SDL_SCANCODE_ESCAPE]
		&& s->current != 0 && s->key_change)
	{
		SDL_WaitEvent(&e->sdl.event);
		check_doublon(s, e->sdl.event.key.keysym.scancode, e->engine.keys)
		? *key = e->sdl.event.key.keysym.scancode : 0;
		s->key_change = 0;
		printf("key pressed : %i\n", *key);
	}
	if ((k[SDL_SCANCODE_RETURN]) && !s->key_change && s->options_menu)
	{
		printf("key CHANGE %i\n", s->key_change);
		s->key_change = 1;
		if (s->current == 0)
		{
			s->sound = !s->sound;
			s->key_change = 0;
		}
	}
}

int	ispoint_inrect(int x, int y, SDL_Rect r)
{
	return (x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h);
}

