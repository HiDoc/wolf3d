/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crs_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:47:50 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 20:47:56 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		crs_del(void **ap)
{
	SDL_Cursor		*cursor;

	cursor = (SDL_Cursor *)(*ap);
	if (ap && *ap)
	{
		SDL_FreeCursor(cursor);
		cursor = 0;
	}
}
