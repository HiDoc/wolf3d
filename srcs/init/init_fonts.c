/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fonts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:29:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 18:02:44 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	underscore_off_name(char *name, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		name[i] == '_' ? name[i] = ' ' : 0;
}

void	ld_fonts(t_env *env)
{
	t_pfont	*f;

	f = &env->hud.font;
	if (!(f->arial = lt_push(TTF_OpenFont(F_ARIAL, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	if (!(f->doom = lt_push(TTF_OpenFont(F_DOOM, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	if (!(f->text = lt_push(TTF_OpenFont(F_TEXT, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	if (!(f->number = lt_push(TTF_OpenFont(F_NUMB, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	if (!(f->quantify = lt_push(TTF_OpenFont(F_QTFY, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
}
