/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:01 by abaille           #+#    #+#             */
/*   Updated: 2019/03/10 22:18:02 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	load_sounds(t_env *env)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	env->sounds.shot = Mix_LoadWAV("rsrc/sound/shot.wav");
}