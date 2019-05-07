/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdw_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:47:21 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 19:48:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	wdw_del(void **ap)
{
	SDL_Window	*window;

	window = (SDL_Window *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyWindow(window);
		window = 0;
	}
}
