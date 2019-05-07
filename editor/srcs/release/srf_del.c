/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srf_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:46:55 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 20:47:04 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		srf_del(void **ap)
{
	SDL_Surface		*surface;

	surface = (SDL_Surface *)(*ap);
	if (ap && *ap)
	{
		SDL_FreeSurface(surface);
		surface = 0;
	}
}
