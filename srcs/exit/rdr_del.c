/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:48:10 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 15:17:43 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	rdr_del(void **ap)
{
	SDL_Renderer	*renderer;

	renderer = (SDL_Renderer *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyRenderer(renderer);
		renderer = 0;
	}
}
