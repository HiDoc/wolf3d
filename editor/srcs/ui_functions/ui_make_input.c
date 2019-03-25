/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:02:05 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 18:48:57 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_make_input(SDL_Surface *surface, t_rect rect, t_data *data)
{
	ui_make_rect(surface, rect);
	ui_make_string(rect, "bonjour", data);
}
