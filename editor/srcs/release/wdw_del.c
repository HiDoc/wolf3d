/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdw_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:45:57 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 20:46:14 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		wdw_del(void **ap)
{
	SDL_Window		*window;

	window = (SDL_Window *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyWindow(window);
		window = 0;
	}
}
