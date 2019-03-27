/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_mouseenter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:43:59 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 16:15:08 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		ui_mouseenter(int x, int y, t_rect rect)
{
	return (x > rect.x && x < rect.x + rect.w
	&& y > rect.y && y < rect.y + rect.h);
}
