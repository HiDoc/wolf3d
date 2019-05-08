/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:55:44 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 20:14:09 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	free_vertex(t_sector *sct)
{
	int	i;

	i = -1;
	while (++i < (int)sct->npoints + 1)
		lt_release((void**)&(sct->vertex[i]));
	i = -1;
	while (++i < (int)sct->npoints)
		lt_release((void**)&(sct->neighbors[i]));
}

static void	free_sct(t_sector *sct)
{
	t_wrap_sect	*w_sect;
	t_wrap_sect	*ws_tmp;
	t_wrap_enmy	*w_enemy;
	t_wrap_enmy	*we_tmp;

	free_vertex(sct);
	w_sect = sct->head_object;
	while (w_sect)
	{
		ws_tmp = w_sect->next;
		lt_release((void**)&w_sect);
		w_sect = ws_tmp;
	}
	w_enemy = sct->head_enemy;
	while (w_enemy)
	{
		we_tmp = w_enemy->next;
		lt_release((void**)&w_enemy);
		w_enemy = we_tmp;
	}
	lt_release((void**)&sct);
}

void		free_map(t_env *env)
{
	int	i;

	i = -1;
	while (++i < (int)env->engine.nsectors)
		free_sct(&(env->engine.sectors[i]));
}
