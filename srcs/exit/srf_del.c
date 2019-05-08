/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srf_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:04:39 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 20:07:46 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	srf_del(void **ap)
{
	SDL_Surface	*surface;

	surface = (SDL_Surface *)(*ap);
	if (ap && *ap)
	{
		SDL_FreeSurface(surface);
		surface = 0;
	}
}
