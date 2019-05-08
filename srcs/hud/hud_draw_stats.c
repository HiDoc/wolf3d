/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw_stats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 02:11:44 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 16:49:44 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		ui_put_fps(t_env *env, int fps)
{
	put_data(env, (t_font){RED, "fps : ",
		env->hud.font.number, (t_vtx){10, 10}, W / 40, -1, fps});
	return (1);
}

void	update_data(t_env *e)
{
	t_stats	*s;

	s = &e->stats;
	s->data[I_KD_RATIO] = (s->data[I_DEATHS])
		? s->data[I_KILLS] / s->data[I_DEATHS] : s->data[I_KILLS];
}

void	print_stats(t_env *e, float size, t_vtx w, t_vtx h)
{
	int			i;
	t_vtx		p;
	char		*t;
	float		div_y;
	const char	*str[NB_STATS - 3] = {D_KILLS, D_DEATHS, D_TIMEPLAY, D_KD_RATIO,
	D_KD_PERMN, D_K_MAGNUM, D_K_SHOTGUN, D_K_RIFLE, D_K_RPG, D_K_FIST};

	i = -1;
	while (++i < NB_STATS - 3)
	{
		p.x = i < 5 ? w.x : w.y;
		div_y = (i == 0 || i == 5) ? h.x : div_y + h.y;
		p.y = H - div_y;
		if (i != 2)
			put_data(e, (t_font){GOLD, str[i], e->hud.font.text, p,
				size, -1, e->stats.data[i + 3]});
		else
		{
			t = time_to_str(SDL_GetTicks() - ((!e->menu.status.gameover)
				? e->levels[e->curr_lvl]->tplay : 0));
			t = ft_strrjoin((char *)str[i], t);
			put_data(e, (t_font){GOLD, t, e->hud.font.text, p, size, -1, -1});
			lt_release((void**)&t);
		}
	}
}
