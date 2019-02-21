/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 17:41:45 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/21 16:40:34 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		load_sounds(t_env *env)
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return (0);
	if (!(env->sounds.shot = Mix_LoadWAV("rsrc/sound/shot.wav")))
		return (0);
	return (1);
}
