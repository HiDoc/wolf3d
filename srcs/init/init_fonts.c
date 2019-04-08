/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fonts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:29:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/08 22:30:07 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		load_fonts(t_env *env)
{
	t_uitxt	*f;

	f = &env->hud.text;
	if (!(f->arial = TTF_OpenFont(F_ARIAL, 100)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont", env);
	if (!(f->doom = TTF_OpenFont(F_DOOM, 100)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont", env);
	if (!(f->text = TTF_OpenFont(F_TEXT, 100)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont", env);
	if (!(f->number = TTF_OpenFont(F_NUMB, 100)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont", env);
}
