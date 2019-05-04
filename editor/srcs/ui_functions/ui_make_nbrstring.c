/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_nbrstring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:18 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/17 01:19:08 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_make_nbrstring(SDL_Rect rect, int value, t_data *data)
{
	char	*str;

	if (!(str = lt_push(ft_itoa(value), ft_memdel)))
		ui_error_exit_sdl("Libui: Error out of memory");
	ui_make_string(rect, str, data);
	lt_release((void**)&str);
}
