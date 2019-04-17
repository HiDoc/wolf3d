/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:33:24 by abaille           #+#    #+#             */
/*   Updated: 2019/04/17 21:36:38 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	launch_msc_menu(t_env *e, t_status *s)
{
	if (s->on)
		Mix_FadeInMusic(e->sound.ambiance[0], 0, 3000) < 0
		? doom_error_exit("Doom_nukem error on Mix_FadeInMusic")
		: 0;
	else
		!Mix_FadeOutMusic(100)
		? doom_error_exit("Doom_nukem error on Mix_FadeOutMusic")
		: 0;

}