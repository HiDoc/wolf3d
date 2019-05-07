/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crs_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:08:48 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 20:09:14 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	crs_del(void **ap)
{
	SDL_Cursor	*cursor;

	cursor = (SDL_Cursor *)(*ap);
	if (ap && *ap)
	{
		SDL_FreeCursor(cursor);
		cursor = 0;
	}
}
