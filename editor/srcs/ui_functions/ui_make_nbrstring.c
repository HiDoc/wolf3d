/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_nbrstring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:18 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/03 17:26:58 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_make_nbrstring(SDL_Rect rect, int value, Uint32 color, t_data *data)
{
	char	*str;

	if (!(str = lt_push(ft_itoa(value), ft_memdel)))
		ui_error_exit_sdl("Libui: Error out of memory");
	ui_make_string(rect, str, color, data);
	lt_release((void**)&str);
}
