/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:49:46 by abaille           #+#    #+#             */
/*   Updated: 2019/04/22 11:43:38 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	create_save_image(t_env *e)
{
	e->stats.save = 1;
	img_scaled_copy(e->sdl.surface, e->stats.save_img);
}

void convert_time(int *hour,int *min,int *sec)
{
	int	timems;

	timems = SDL_GetTicks();
	timems /= 1000;
	*sec = timems % 60;
	timems /= 60;
	*min = timems % 60;
	timems /= 60;
	*hour = timems;
}

void	create_save_name(char **name)
{
	int		hour;
	int		min;
	int		sec;
	char	*t;

	convert_time(&hour, &min, &sec);
	t = ft_itoa(hour);
	*name = ft_strljoin(t, " h ");
	t = ft_itoa(min);
	*name = ft_strljoin(*name, t);
	lt_release(t);
	t = ft_itoa(sec);
	*name = ft_strljoin(*name, " mn ");
	*name = ft_strljoin(*name, t);
	*name = ft_strljoin(*name, " sec");
	lt_release(t);
}

t_bloc	*new_save(t_env *e)
{
	t_bloc		*new;

	new = ft_memalloc(sizeof(t_bloc));
	make_surface(W / 10, H / 10);
	img_scaled_copy(e->stats.save_img, new->use.sprite);
	new->use.rect = (SDL_Rect){W / 2.5, H / 3, W / 10, H / 10};
	create_save_name(&new->name);
	new->rect = (SDL_Rect){W / 2.5, H / 2.5, W / 40, 0};
	new->next = NULL;
	return (new);
}

void	create_save(t_env *e, t_status *s)
{
	t_bloc		*cur_save;

	if (e->stats.save)
	{
		s->nb_save++;
		s->nb_save < 6 ? e->menu.status.end++ : 0;
		cur_save = e->menu.save_game;
		while (cur_save->next != NULL)
			cur_save = cur_save->next;
		cur_save->next = new_save(e);
		ui_put_data(e, (t_font){M_WHITE, "Game saved", e->hud.text.quantify,
			(t_vtx){W / 2, H / 20}, W / 60, -1, -1});
		e->stats.save = 0;
	}
	else
		ui_put_data(e, (t_font){M_WHITE, "Already saved", e->hud.text.quantify,
			(t_vtx){W / 1.5, H / 20}, W / 60, -1, -1});
}