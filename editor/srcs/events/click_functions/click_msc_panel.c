/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_msc_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:23:35 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 14:51:58 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			click_msc_miscup(t_env *env)
{
	if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
		(env->editor.dropdown[DD_BGAUDIO].idx_element < 0)
			? env->editor.dropdown[DD_BGAUDIO].idx_element++ : 0;
	else if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
		(env->editor.dropdown[DD_SBTX].idx_element < 0)
			? env->editor.dropdown[DD_SBTX].idx_element++ : 0;
}

void			click_msc_miscdown(t_env *env)
{
	t_dropdown	*dd_audio;
	t_dropdown	*dd_sbtx;

	dd_audio = &env->editor.dropdown[DD_BGAUDIO];
	dd_sbtx = &env->editor.dropdown[DD_SBTX];
	if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
		(dd_audio->idx_element > -dd_audio->nb_element + 1)
			? dd_audio->idx_element-- : 0;
	else if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
		(dd_sbtx->idx_element > -dd_sbtx->nb_element + 1)
			? dd_sbtx->idx_element-- : 0;
}

void			click_msc_music(t_env *env)
{
	get_element(E_B_SELEC_MUSIC, env)->clicked = 1;
	get_element(E_B_SELEC_SBTX, env)->clicked = 0;
}

void			click_msc_sbtx(t_env *env)
{
	get_element(E_B_SELEC_SBTX, env)->clicked = 1;
	get_element(E_B_SELEC_MUSIC, env)->clicked = 0;
}

void			click_msc_music_btn(t_env *env)
{
	if (Mix_PlayMusic(env->editor.dropdown[DD_BGAUDIO].current->audio, -1) < 0)
		ui_error_exit_sdl("Editor error on Mix_PlayMusic");
	env->editor.dropdown[DD_BGAUDIO].current->clicked = 1;
}

void			click_msc_sbtx_btn(t_env *env)
{
	env->editor.dropdown[DD_SBTX].current->clicked = 1;
}
