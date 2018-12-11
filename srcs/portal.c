/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:54:17 by fmadura           #+#    #+#             */
/*   Updated: 2018/12/11 14:54:19 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_point	portal_pos(t_env *env, t_point pos)
{
	if (env->w_map[(int)(pos.x + env->dir.x * 0.2)][(int)pos.y] == 0)
		pos.x += env->dir.x * (0.2 / 2.0);
	else
		env->portal.hit = 1;
	if (env->w_map[(int)pos.x][(int)(pos.y + env->dir.y * 0.2)] == 0)
		pos.y += env->dir.y * (0.2 / 2.0);
	else
		env->portal.hit = 2;
	return (pos);
}

/*
** pour lancer la fenetre de sortie appuie sur X en visant un mur
** et pour lancer la fenetre d entree avec l image de sortie appuie sur A
** y a aucune protection verif etc donc pour l instant si tu reclic
** sur d autres murs t auras les mm img ptet mm que ca va buguer ^^
*/
