/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msc_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:46:37 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 19:47:13 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	msc_del(void **ap)
{
	Mix_Music	*music;

	music = (Mix_Music *)(*ap);
	if (ap && *ap)
	{
		Mix_FreeMusic(music);
		music = 0;
	}
}
