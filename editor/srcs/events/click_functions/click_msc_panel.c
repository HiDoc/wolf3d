/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_msc_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:23:35 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 18:19:30 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

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
