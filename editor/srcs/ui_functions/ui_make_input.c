/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:02:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/26 15:44:28 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_make_input(SDL_Surface *surface, t_elem *elem, t_data *data)
{
	ui_make_rect(surface, elem->rect);
	if (elem->str)
	{
		if (!(ui_make_string(elem->rect, elem->str, data)))
			elem->str_max = 1;
		else
			elem->str_max = 0;
	}
}
