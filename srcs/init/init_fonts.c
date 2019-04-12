/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fonts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:29:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/11 23:41:15 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		load_fonts(t_env *env)
{
	t_uitxt	*f;

	f = &env->hud.text;
	if (!(f->arial = lt_push(TTF_OpenFont(F_ARIAL, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	if (!(f->doom = lt_push(TTF_OpenFont(F_DOOM, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	if (!(f->text = lt_push(TTF_OpenFont(F_TEXT, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	if (!(f->doom200 = lt_push(TTF_OpenFont(F_DOOM, 200), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	if (!(f->text200 = lt_push(TTF_OpenFont(F_TEXT, 200), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	if (!(f->number = lt_push(TTF_OpenFont(F_NUMB, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
}
