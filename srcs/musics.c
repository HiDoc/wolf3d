/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 17:41:45 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/08 13:56:37 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	load_sounds(t_env *env)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	env->sounds.shot = Mix_LoadWAV("rsrc/sound/shot.wav");
}
