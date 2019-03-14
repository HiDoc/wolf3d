/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_nbrstring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:18 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/04 10:25:58 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		ui_make_nbrstring(t_rect rect, int value, t_data *data)
{
	char	*str;

	if (!(str = ft_itoa(value)))
		ui_error_exit_sdl("Libui: Error out of memory", data);
	ui_make_string(rect, str, data);
	free(str);
}
