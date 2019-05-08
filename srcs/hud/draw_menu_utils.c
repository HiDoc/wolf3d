/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:54:01 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 17:56:31 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char	*which_str_menu(t_env *e, int limit, const char *s, int i)
{
	char		*p;
	t_status	*st;

	st = &e->menu.status;
	if (limit == NB_OPT_MENU && !i)
		p = ft_strljoin(ft_itoa(st->msc_vol), (char*)s);
	else if (limit != NB_OPT_MENU || (st->cur == i && st->key_change))
		p = ft_strdup(s);
	else
		p = ft_strjoin(s, (char*)SDL_GetScancodeName(e->engine.keys[i]));
	return (p);
}
